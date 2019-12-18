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
struct usb_serial {TYPE_1__* interface; } ;
struct cp210x_serial_private {int /*<<< orphan*/  partnum; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP210X_GET_PARTNUM ; 
 int /*<<< orphan*/  CP210X_PARTNUM_UNKNOWN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  REQTYPE_DEVICE_TO_HOST ; 
 int cp210x_gpio_init (struct usb_serial*) ; 
 int /*<<< orphan*/  cp210x_init_max_speed (struct usb_serial*) ; 
 int cp210x_read_vendor_block (struct usb_serial*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct cp210x_serial_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_serial_data (struct usb_serial*,struct cp210x_serial_private*) ; 

__attribute__((used)) static int cp210x_attach(struct usb_serial *serial)
{
	int result;
	struct cp210x_serial_private *priv;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	result = cp210x_read_vendor_block(serial, REQTYPE_DEVICE_TO_HOST,
					  CP210X_GET_PARTNUM, &priv->partnum,
					  sizeof(priv->partnum));
	if (result < 0) {
		dev_warn(&serial->interface->dev,
			 "querying part number failed\n");
		priv->partnum = CP210X_PARTNUM_UNKNOWN;
	}

	usb_set_serial_data(serial, priv);

	cp210x_init_max_speed(serial);

	result = cp210x_gpio_init(serial);
	if (result < 0) {
		dev_err(&serial->interface->dev, "GPIO initialisation failed: %d\n",
				result);
	}

	return 0;
}