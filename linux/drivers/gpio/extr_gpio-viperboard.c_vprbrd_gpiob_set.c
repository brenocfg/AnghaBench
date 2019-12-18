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
struct vprbrd_gpiob_msg {void* mask; void* val; int /*<<< orphan*/  cmd; } ;
struct vprbrd_gpio {int gpiob_out; int gpiob_val; struct vprbrd* vb; } ;
struct vprbrd {int /*<<< orphan*/  lock; int /*<<< orphan*/  usb_dev; scalar_t__ buf; } ;
struct gpio_chip {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPRBRD_GPIOB_CMD_SETVAL ; 
 int /*<<< orphan*/  VPRBRD_USB_REQUEST_GPIOB ; 
 int /*<<< orphan*/  VPRBRD_USB_TIMEOUT_MS ; 
 int /*<<< orphan*/  VPRBRD_USB_TYPE_OUT ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct vprbrd_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct vprbrd_gpiob_msg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vprbrd_gpiob_set(struct gpio_chip *chip,
		unsigned int offset, int value)
{
	int ret;
	struct vprbrd_gpio *gpio = gpiochip_get_data(chip);
	struct vprbrd *vb = gpio->vb;
	struct vprbrd_gpiob_msg *gbmsg = (struct vprbrd_gpiob_msg *)vb->buf;

	if (gpio->gpiob_out & (1 << offset)) {
		if (value)
			gpio->gpiob_val |= (1 << offset);
		else
			gpio->gpiob_val &= ~(1 << offset);

		mutex_lock(&vb->lock);

		gbmsg->cmd = VPRBRD_GPIOB_CMD_SETVAL;
		gbmsg->val = cpu_to_be16(value << offset);
		gbmsg->mask = cpu_to_be16(0x0001 << offset);

		ret = usb_control_msg(vb->usb_dev,
			usb_sndctrlpipe(vb->usb_dev, 0),
			VPRBRD_USB_REQUEST_GPIOB, VPRBRD_USB_TYPE_OUT,
			0x0000,	0x0000, gbmsg,
			sizeof(struct vprbrd_gpiob_msg), VPRBRD_USB_TIMEOUT_MS);

		mutex_unlock(&vb->lock);

		if (ret != sizeof(struct vprbrd_gpiob_msg))
			dev_err(chip->parent, "usb error setting pin value\n");
	}
}