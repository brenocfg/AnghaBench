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
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;
struct bttv {TYPE_1__ c; } ;

/* Variables and functions */
 scalar_t__ bttv_gpio ; 
 int /*<<< orphan*/  bttv_gpio_tracking (struct bttv*,char*) ; 
 scalar_t__ bttv_verbose ; 
 int /*<<< orphan*/  gpio_bits (int,int) ; 
 int /*<<< orphan*/  gpio_inout (int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void boot_msp34xx(struct bttv *btv, int pin)
{
	int mask = (1 << pin);

	gpio_inout(mask,mask);
	gpio_bits(mask,0);
	mdelay(2);
	udelay(500);
	gpio_bits(mask,mask);

	if (bttv_gpio)
		bttv_gpio_tracking(btv,"msp34xx");
	if (bttv_verbose)
		pr_info("%d: Hauppauge/Voodoo msp34xx: reset line init [%d]\n",
			btv->c.nr, pin);
}