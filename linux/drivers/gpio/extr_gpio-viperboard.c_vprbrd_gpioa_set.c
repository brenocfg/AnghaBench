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
struct vprbrd_gpioa_msg {int clk; unsigned int offset; int t1; int t2; int invert; int pwmlevel; int outval; int risefall; int answer; int __fill; int /*<<< orphan*/  cmd; } ;
struct vprbrd_gpio {int gpioa_out; int gpioa_val; struct vprbrd* vb; } ;
struct vprbrd {int /*<<< orphan*/  lock; int /*<<< orphan*/  usb_dev; scalar_t__ buf; } ;
struct gpio_chip {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPRBRD_GPIOA_CMD_SETOUT ; 
 int /*<<< orphan*/  VPRBRD_USB_REQUEST_GPIOA ; 
 int /*<<< orphan*/  VPRBRD_USB_TIMEOUT_MS ; 
 int /*<<< orphan*/  VPRBRD_USB_TYPE_OUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct vprbrd_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct vprbrd_gpioa_msg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vprbrd_gpioa_set(struct gpio_chip *chip,
		unsigned int offset, int value)
{
	int ret;
	struct vprbrd_gpio *gpio = gpiochip_get_data(chip);
	struct vprbrd *vb = gpio->vb;
	struct vprbrd_gpioa_msg *gamsg = (struct vprbrd_gpioa_msg *)vb->buf;

	if (gpio->gpioa_out & (1 << offset)) {
		if (value)
			gpio->gpioa_val |= (1 << offset);
		else
			gpio->gpioa_val &= ~(1 << offset);

		mutex_lock(&vb->lock);

		gamsg->cmd = VPRBRD_GPIOA_CMD_SETOUT;
		gamsg->clk = 0x00;
		gamsg->offset = offset;
		gamsg->t1 = 0x00;
		gamsg->t2 = 0x00;
		gamsg->invert = 0x00;
		gamsg->pwmlevel = 0x00;
		gamsg->outval = value;
		gamsg->risefall = 0x00;
		gamsg->answer = 0x00;
		gamsg->__fill = 0x00;

		ret = usb_control_msg(vb->usb_dev,
			usb_sndctrlpipe(vb->usb_dev, 0),
			VPRBRD_USB_REQUEST_GPIOA, VPRBRD_USB_TYPE_OUT,
			0x0000,	0x0000, gamsg,
			sizeof(struct vprbrd_gpioa_msg), VPRBRD_USB_TIMEOUT_MS);

		mutex_unlock(&vb->lock);

		if (ret != sizeof(struct vprbrd_gpioa_msg))
			dev_err(chip->parent, "usb error setting pin value\n");
	}
}