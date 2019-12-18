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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct hso_tiocmget {int /*<<< orphan*/  waitq; int /*<<< orphan*/  mutex; scalar_t__ urb; void* endp; void* serial_state_notification; } ;
struct hso_serial_state_notification {int dummy; } ;
struct TYPE_2__ {struct hso_serial* dev_serial; } ;
struct hso_serial {int /*<<< orphan*/  minor; int /*<<< orphan*/  write_data; void* out_endp; void* in_endp; struct hso_tiocmget* tiocmget; TYPE_1__ port_data; struct hso_serial* parent; } ;
struct hso_device {int /*<<< orphan*/  minor; int /*<<< orphan*/  write_data; void* out_endp; void* in_endp; struct hso_tiocmget* tiocmget; TYPE_1__ port_data; struct hso_device* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  BULK_URB_RX_SIZE ; 
 int /*<<< orphan*/  BULK_URB_TX_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HSO_PORT_MASK ; 
 int HSO_PORT_MODEM ; 
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  USB_DIR_OUT ; 
 int /*<<< orphan*/  USB_ENDPOINT_XFER_BULK ; 
 int /*<<< orphan*/  USB_ENDPOINT_XFER_INT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct hso_serial* hso_create_device (struct usb_interface*,int) ; 
 int /*<<< orphan*/  hso_free_tiomget (struct hso_serial*) ; 
 void* hso_get_ep (struct usb_interface*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hso_log_port (struct hso_serial*) ; 
 scalar_t__ hso_serial_common_create (struct hso_serial*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hso_serial_common_free (struct hso_serial*) ; 
 int /*<<< orphan*/  hso_serial_tty_unregister (struct hso_serial*) ; 
 int /*<<< orphan*/  hso_std_serial_write_data ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hso_serial*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_serial_by_index (int /*<<< orphan*/ ,struct hso_serial*) ; 
 scalar_t__ usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hso_device *hso_create_bulk_serial_device(
			struct usb_interface *interface, int port)
{
	struct hso_device *hso_dev;
	struct hso_serial *serial;
	int num_urbs;
	struct hso_tiocmget *tiocmget;

	hso_dev = hso_create_device(interface, port);
	if (!hso_dev)
		return NULL;

	serial = kzalloc(sizeof(*serial), GFP_KERNEL);
	if (!serial)
		goto exit;

	serial->parent = hso_dev;
	hso_dev->port_data.dev_serial = serial;

	if ((port & HSO_PORT_MASK) == HSO_PORT_MODEM) {
		num_urbs = 2;
		serial->tiocmget = kzalloc(sizeof(struct hso_tiocmget),
					   GFP_KERNEL);
		serial->tiocmget->serial_state_notification
			= kzalloc(sizeof(struct hso_serial_state_notification),
					   GFP_KERNEL);
		/* it isn't going to break our heart if serial->tiocmget
		 *  allocation fails don't bother checking this.
		 */
		if (serial->tiocmget && serial->tiocmget->serial_state_notification) {
			tiocmget = serial->tiocmget;
			tiocmget->endp = hso_get_ep(interface,
						    USB_ENDPOINT_XFER_INT,
						    USB_DIR_IN);
			if (!tiocmget->endp) {
				dev_err(&interface->dev, "Failed to find INT IN ep\n");
				goto exit;
			}

			tiocmget->urb = usb_alloc_urb(0, GFP_KERNEL);
			if (tiocmget->urb) {
				mutex_init(&tiocmget->mutex);
				init_waitqueue_head(&tiocmget->waitq);
			} else
				hso_free_tiomget(serial);
		}
	}
	else
		num_urbs = 1;

	if (hso_serial_common_create(serial, num_urbs, BULK_URB_RX_SIZE,
				     BULK_URB_TX_SIZE))
		goto exit;

	serial->in_endp = hso_get_ep(interface, USB_ENDPOINT_XFER_BULK,
				     USB_DIR_IN);
	if (!serial->in_endp) {
		dev_err(&interface->dev, "Failed to find BULK IN ep\n");
		goto exit2;
	}

	if (!
	    (serial->out_endp =
	     hso_get_ep(interface, USB_ENDPOINT_XFER_BULK, USB_DIR_OUT))) {
		dev_err(&interface->dev, "Failed to find BULK IN ep\n");
		goto exit2;
	}

	serial->write_data = hso_std_serial_write_data;

	/* and record this serial */
	set_serial_by_index(serial->minor, serial);

	/* setup the proc dirs and files if needed */
	hso_log_port(hso_dev);

	/* done, return it */
	return hso_dev;

exit2:
	hso_serial_tty_unregister(serial);
	hso_serial_common_free(serial);
exit:
	hso_free_tiomget(serial);
	kfree(serial);
	kfree(hso_dev);
	return NULL;
}