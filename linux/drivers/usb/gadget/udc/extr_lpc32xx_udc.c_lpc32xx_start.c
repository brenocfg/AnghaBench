#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_gadget_driver {scalar_t__ max_speed; int /*<<< orphan*/  setup; } ;
struct usb_gadget {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_5__ {int is_selfpowered; TYPE_1__ dev; } ;
struct lpc32xx_udc {int enabled; int /*<<< orphan*/  isp1301_i2c_client; scalar_t__ vbus; scalar_t__ last_vbus; TYPE_2__ gadget; TYPE_3__* dev; struct usb_gadget_driver* driver; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int INT_SESS_VLD ; 
 int INT_VBUS_VLD ; 
 int /*<<< orphan*/  ISP1301_I2C_INTERRUPT_FALLING ; 
 int /*<<< orphan*/  ISP1301_I2C_INTERRUPT_RISING ; 
 scalar_t__ USB_SPEED_FULL ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct lpc32xx_udc* to_udc (struct usb_gadget*) ; 
 int /*<<< orphan*/  vbus_work (struct lpc32xx_udc*) ; 

__attribute__((used)) static int lpc32xx_start(struct usb_gadget *gadget,
			 struct usb_gadget_driver *driver)
{
	struct lpc32xx_udc *udc = to_udc(gadget);

	if (!driver || driver->max_speed < USB_SPEED_FULL || !driver->setup) {
		dev_err(udc->dev, "bad parameter.\n");
		return -EINVAL;
	}

	if (udc->driver) {
		dev_err(udc->dev, "UDC already has a gadget driver\n");
		return -EBUSY;
	}

	udc->driver = driver;
	udc->gadget.dev.of_node = udc->dev->of_node;
	udc->enabled = 1;
	udc->gadget.is_selfpowered = 1;
	udc->vbus = 0;

	/* Force VBUS process once to check for cable insertion */
	udc->last_vbus = udc->vbus = 0;
	vbus_work(udc);

	/* enable interrupts */
	i2c_smbus_write_byte_data(udc->isp1301_i2c_client,
		ISP1301_I2C_INTERRUPT_FALLING, INT_SESS_VLD | INT_VBUS_VLD);
	i2c_smbus_write_byte_data(udc->isp1301_i2c_client,
		ISP1301_I2C_INTERRUPT_RISING, INT_SESS_VLD | INT_VBUS_VLD);

	return 0;
}