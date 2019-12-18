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
struct usb_interface {int dummy; } ;
struct hso_shared_int {int /*<<< orphan*/  shared_int_lock; int /*<<< orphan*/  ref_count; } ;
struct TYPE_2__ {struct hso_serial* dev_serial; } ;
struct hso_serial {int /*<<< orphan*/  minor; struct hso_shared_int* shared_int; int /*<<< orphan*/  write_data; int /*<<< orphan*/  tx_data_length; struct hso_serial* parent; TYPE_1__ port_data; } ;
struct hso_device {int /*<<< orphan*/  minor; struct hso_shared_int* shared_int; int /*<<< orphan*/  write_data; int /*<<< orphan*/  tx_data_length; struct hso_device* parent; TYPE_1__ port_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_URB_RX_SIZE ; 
 int /*<<< orphan*/  CTRL_URB_TX_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HSO_INTF_MUX ; 
 int HSO_PORT_MASK ; 
 int HSO_PORT_NO_PORT ; 
 struct hso_serial* hso_create_device (struct usb_interface*,int) ; 
 int /*<<< orphan*/  hso_log_port (struct hso_serial*) ; 
 int /*<<< orphan*/  hso_mux_serial_write_data ; 
 int hso_mux_to_port (int) ; 
 scalar_t__ hso_serial_common_create (struct hso_serial*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hso_serial*) ; 
 struct hso_serial* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_serial_by_index (int /*<<< orphan*/ ,struct hso_serial*) ; 
 int /*<<< orphan*/  tty_drv ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
struct hso_device *hso_create_mux_serial_device(struct usb_interface *interface,
						int port,
						struct hso_shared_int *mux)
{
	struct hso_device *hso_dev;
	struct hso_serial *serial;
	int port_spec;

	port_spec = HSO_INTF_MUX;
	port_spec &= ~HSO_PORT_MASK;

	port_spec |= hso_mux_to_port(port);
	if ((port_spec & HSO_PORT_MASK) == HSO_PORT_NO_PORT)
		return NULL;

	hso_dev = hso_create_device(interface, port_spec);
	if (!hso_dev)
		return NULL;

	serial = kzalloc(sizeof(*serial), GFP_KERNEL);
	if (!serial)
		goto exit;

	hso_dev->port_data.dev_serial = serial;
	serial->parent = hso_dev;

	if (hso_serial_common_create
	    (serial, 1, CTRL_URB_RX_SIZE, CTRL_URB_TX_SIZE))
		goto exit;

	serial->tx_data_length--;
	serial->write_data = hso_mux_serial_write_data;

	serial->shared_int = mux;
	mutex_lock(&serial->shared_int->shared_int_lock);
	serial->shared_int->ref_count++;
	mutex_unlock(&serial->shared_int->shared_int_lock);

	/* and record this serial */
	set_serial_by_index(serial->minor, serial);

	/* setup the proc dirs and files if needed */
	hso_log_port(hso_dev);

	/* done, return it */
	return hso_dev;

exit:
	if (serial) {
		tty_unregister_device(tty_drv, serial->minor);
		kfree(serial);
	}
	kfree(hso_dev);
	return NULL;

}