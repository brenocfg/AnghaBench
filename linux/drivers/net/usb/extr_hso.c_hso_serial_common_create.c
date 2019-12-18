#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hso_serial {int minor; int num_rx_urbs; int rx_data_length; int tx_data_length; void* tx_buffer; void* tx_data; scalar_t__ tx_buffer_count; scalar_t__ tx_data_count; TYPE_3__* tx_urb; void** rx_data; TYPE_2__** rx_urb; int /*<<< orphan*/  serial_lock; int /*<<< orphan*/  magic; TYPE_4__* parent; int /*<<< orphan*/  port; } ;
struct TYPE_8__ {TYPE_1__* interface; int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {scalar_t__ transfer_buffer_length; int /*<<< orphan*/ * transfer_buffer; } ;
struct TYPE_6__ {scalar_t__ transfer_buffer_length; int /*<<< orphan*/ * transfer_buffer; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HSO_SERIAL_MAGIC ; 
 int get_free_serial_index () ; 
 int /*<<< orphan*/  hso_serial_common_free (struct hso_serial*) ; 
 int /*<<< orphan*/  hso_serial_dev_groups ; 
 int /*<<< orphan*/  hso_serial_tty_unregister (struct hso_serial*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_drv ; 
 int /*<<< orphan*/  tty_port_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_register_device_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hso_serial_common_create(struct hso_serial *serial, int num_urbs,
				    int rx_size, int tx_size)
{
	int minor;
	int i;

	tty_port_init(&serial->port);

	minor = get_free_serial_index();
	if (minor < 0)
		goto exit;

	/* register our minor number */
	serial->parent->dev = tty_port_register_device_attr(&serial->port,
			tty_drv, minor, &serial->parent->interface->dev,
			serial->parent, hso_serial_dev_groups);

	/* fill in specific data for later use */
	serial->minor = minor;
	serial->magic = HSO_SERIAL_MAGIC;
	spin_lock_init(&serial->serial_lock);
	serial->num_rx_urbs = num_urbs;

	/* RX, allocate urb and initialize */

	/* prepare our RX buffer */
	serial->rx_data_length = rx_size;
	for (i = 0; i < serial->num_rx_urbs; i++) {
		serial->rx_urb[i] = usb_alloc_urb(0, GFP_KERNEL);
		if (!serial->rx_urb[i])
			goto exit;
		serial->rx_urb[i]->transfer_buffer = NULL;
		serial->rx_urb[i]->transfer_buffer_length = 0;
		serial->rx_data[i] = kzalloc(serial->rx_data_length,
					     GFP_KERNEL);
		if (!serial->rx_data[i])
			goto exit;
	}

	/* TX, allocate urb and initialize */
	serial->tx_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!serial->tx_urb)
		goto exit;
	serial->tx_urb->transfer_buffer = NULL;
	serial->tx_urb->transfer_buffer_length = 0;
	/* prepare our TX buffer */
	serial->tx_data_count = 0;
	serial->tx_buffer_count = 0;
	serial->tx_data_length = tx_size;
	serial->tx_data = kzalloc(serial->tx_data_length, GFP_KERNEL);
	if (!serial->tx_data)
		goto exit;

	serial->tx_buffer = kzalloc(serial->tx_data_length, GFP_KERNEL);
	if (!serial->tx_buffer)
		goto exit;

	return 0;
exit:
	hso_serial_tty_unregister(serial);
	hso_serial_common_free(serial);
	return -1;
}