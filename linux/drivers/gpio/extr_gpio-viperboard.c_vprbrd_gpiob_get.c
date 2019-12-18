#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct vprbrd_gpiob_msg {int /*<<< orphan*/  val; } ;
struct vprbrd_gpio {int gpiob_out; int gpiob_val; struct vprbrd* vb; } ;
struct vprbrd {int /*<<< orphan*/  lock; int /*<<< orphan*/  usb_dev; scalar_t__ buf; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPRBRD_USB_REQUEST_GPIOB ; 
 int /*<<< orphan*/  VPRBRD_USB_TIMEOUT_MS ; 
 int /*<<< orphan*/  VPRBRD_USB_TYPE_IN ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct vprbrd_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct vprbrd_gpiob_msg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vprbrd_gpiob_get(struct gpio_chip *chip,
		unsigned int offset)
{
	int ret;
	u16 val;
	struct vprbrd_gpio *gpio = gpiochip_get_data(chip);
	struct vprbrd *vb = gpio->vb;
	struct vprbrd_gpiob_msg *gbmsg = (struct vprbrd_gpiob_msg *)vb->buf;

	/* if io is set to output, just return the saved value */
	if (gpio->gpiob_out & (1 << offset))
		return gpio->gpiob_val & (1 << offset);

	mutex_lock(&vb->lock);

	ret = usb_control_msg(vb->usb_dev, usb_rcvctrlpipe(vb->usb_dev, 0),
		VPRBRD_USB_REQUEST_GPIOB, VPRBRD_USB_TYPE_IN, 0x0000,
		0x0000, gbmsg,	sizeof(struct vprbrd_gpiob_msg),
		VPRBRD_USB_TIMEOUT_MS);
	val = gbmsg->val;

	mutex_unlock(&vb->lock);

	if (ret != sizeof(struct vprbrd_gpiob_msg))
		return ret;

	/* cache the read values */
	gpio->gpiob_val = be16_to_cpu(val);

	return (gpio->gpiob_val >> offset) & 0x1;
}