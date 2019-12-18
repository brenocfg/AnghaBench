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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct snd_tea575x {struct bttv* private_data; } ;
struct bttv_tea575x_gpio {int data; int most; } ;
struct bttv {int mbox_ior; int mbox_csel; int mbox_iow; struct bttv_tea575x_gpio tea_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEA575X_DATA ; 
 int /*<<< orphan*/  TEA575X_MOST ; 
 int /*<<< orphan*/  gpio_bits (int,int) ; 
 int gpio_read () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u8 bttv_tea575x_get_pins(struct snd_tea575x *tea)
{
	struct bttv *btv = tea->private_data;
	struct bttv_tea575x_gpio gpio = btv->tea_gpio;
	u8 ret = 0;
	u16 val;

	if (btv->mbox_ior) {
		/* IOR and CSEL active */
		gpio_bits(btv->mbox_ior | btv->mbox_csel, 0);
		udelay(5);
	}
	val = gpio_read();
	if (btv->mbox_ior) {
		/* all inactive */
		gpio_bits(btv->mbox_ior | btv->mbox_iow | btv->mbox_csel,
			  btv->mbox_ior | btv->mbox_iow | btv->mbox_csel);
	}

	if (val & (1 << gpio.data))
		ret |= TEA575X_DATA;
	if (val & (1 << gpio.most))
		ret |= TEA575X_MOST;

	return ret;
}