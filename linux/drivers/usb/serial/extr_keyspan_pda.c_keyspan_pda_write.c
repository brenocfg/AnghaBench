#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct usb_serial_port {int bulk_out_size; int /*<<< orphan*/  write_urbs_free; int /*<<< orphan*/  dev; TYPE_1__* write_urb; int /*<<< orphan*/  lock; struct usb_serial* serial; } ;
struct usb_serial {int /*<<< orphan*/  dev; } ;
struct tty_struct {int dummy; } ;
struct keyspan_pda_private {int tx_throttled; int tx_room; int /*<<< orphan*/  unthrottle_work; } ;
struct TYPE_2__ {int transfer_buffer_length; int /*<<< orphan*/  transfer_buffer; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int) ; 
 struct keyspan_pda_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int keyspan_pda_write(struct tty_struct *tty,
	struct usb_serial_port *port, const unsigned char *buf, int count)
{
	struct usb_serial *serial = port->serial;
	int request_unthrottle = 0;
	int rc = 0;
	struct keyspan_pda_private *priv;

	priv = usb_get_serial_port_data(port);
	/* guess how much room is left in the device's ring buffer, and if we
	   want to send more than that, check first, updating our notion of
	   what is left. If our write will result in no room left, ask the
	   device to give us an interrupt when the room available rises above
	   a threshold, and hold off all writers (eventually, those using
	   select() or poll() too) until we receive that unthrottle interrupt.
	   Block if we can't write anything at all, otherwise write as much as
	   we can. */
	if (count == 0) {
		dev_dbg(&port->dev, "write request of 0 bytes\n");
		return 0;
	}

	/* we might block because of:
	   the TX urb is in-flight (wait until it completes)
	   the device is full (wait until it says there is room)
	*/
	spin_lock_bh(&port->lock);
	if (!test_bit(0, &port->write_urbs_free) || priv->tx_throttled) {
		spin_unlock_bh(&port->lock);
		return 0;
	}
	clear_bit(0, &port->write_urbs_free);
	spin_unlock_bh(&port->lock);

	/* At this point the URB is in our control, nobody else can submit it
	   again (the only sudden transition was the one from EINPROGRESS to
	   finished).  Also, the tx process is not throttled. So we are
	   ready to write. */

	count = (count > port->bulk_out_size) ? port->bulk_out_size : count;

	/* Check if we might overrun the Tx buffer.   If so, ask the
	   device how much room it really has.  This is done only on
	   scheduler time, since usb_control_msg() sleeps. */
	if (count > priv->tx_room && !in_interrupt()) {
		u8 *room;

		room = kmalloc(1, GFP_KERNEL);
		if (!room) {
			rc = -ENOMEM;
			goto exit;
		}

		rc = usb_control_msg(serial->dev,
				     usb_rcvctrlpipe(serial->dev, 0),
				     6, /* write_room */
				     USB_TYPE_VENDOR | USB_RECIP_INTERFACE
				     | USB_DIR_IN,
				     0, /* value: 0 means "remaining room" */
				     0, /* index */
				     room,
				     1,
				     2000);
		if (rc > 0) {
			dev_dbg(&port->dev, "roomquery says %d\n", *room);
			priv->tx_room = *room;
		}
		kfree(room);
		if (rc < 0) {
			dev_dbg(&port->dev, "roomquery failed\n");
			goto exit;
		}
		if (rc == 0) {
			dev_dbg(&port->dev, "roomquery returned 0 bytes\n");
			rc = -EIO; /* device didn't return any data */
			goto exit;
		}
	}
	if (count > priv->tx_room) {
		/* we're about to completely fill the Tx buffer, so
		   we'll be throttled afterwards. */
		count = priv->tx_room;
		request_unthrottle = 1;
	}

	if (count) {
		/* now transfer data */
		memcpy(port->write_urb->transfer_buffer, buf, count);
		/* send the data out the bulk port */
		port->write_urb->transfer_buffer_length = count;

		priv->tx_room -= count;

		rc = usb_submit_urb(port->write_urb, GFP_ATOMIC);
		if (rc) {
			dev_dbg(&port->dev, "usb_submit_urb(write bulk) failed\n");
			goto exit;
		}
	} else {
		/* There wasn't any room left, so we are throttled until
		   the buffer empties a bit */
		request_unthrottle = 1;
	}

	if (request_unthrottle) {
		priv->tx_throttled = 1; /* block writers */
		schedule_work(&priv->unthrottle_work);
	}

	rc = count;
exit:
	if (rc < 0)
		set_bit(0, &port->write_urbs_free);
	return rc;
}