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
typedef  int u8 ;
typedef  int u16 ;
struct snd_tea575x {struct bttv* private_data; } ;
struct bttv_tea575x_gpio {int data; int clk; int wren; } ;
struct bttv {int mbox_ior; int mbox_iow; int mbox_csel; struct bttv_tea575x_gpio tea_gpio; } ;

/* Variables and functions */
 int TEA575X_CLK ; 
 int TEA575X_DATA ; 
 int TEA575X_WREN ; 
 int /*<<< orphan*/  gpio_bits (int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void bttv_tea575x_set_pins(struct snd_tea575x *tea, u8 pins)
{
	struct bttv *btv = tea->private_data;
	struct bttv_tea575x_gpio gpio = btv->tea_gpio;
	u16 val = 0;

	val |= (pins & TEA575X_DATA) ? (1 << gpio.data) : 0;
	val |= (pins & TEA575X_CLK)  ? (1 << gpio.clk)  : 0;
	val |= (pins & TEA575X_WREN) ? (1 << gpio.wren) : 0;

	gpio_bits((1 << gpio.data) | (1 << gpio.clk) | (1 << gpio.wren), val);
	if (btv->mbox_ior) {
		/* IOW and CSEL active */
		gpio_bits(btv->mbox_iow | btv->mbox_csel, 0);
		udelay(5);
		/* all inactive */
		gpio_bits(btv->mbox_ior | btv->mbox_iow | btv->mbox_csel,
			  btv->mbox_ior | btv->mbox_iow | btv->mbox_csel);
	}
}