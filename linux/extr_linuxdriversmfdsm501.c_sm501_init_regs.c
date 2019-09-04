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
struct TYPE_2__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  set; } ;
struct sm501_initdata {scalar_t__ mclk; scalar_t__ m1xclk; int /*<<< orphan*/  gpio_high; int /*<<< orphan*/  gpio_low; int /*<<< orphan*/  misc_timing; TYPE_1__ misc_control; } ;
struct sm501_devdata {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SM501_CLOCK_M1XCLK ; 
 int /*<<< orphan*/  SM501_CLOCK_MCLK ; 
 int /*<<< orphan*/  SM501_GPIO31_0_CONTROL ; 
 int /*<<< orphan*/  SM501_GPIO63_32_CONTROL ; 
 int /*<<< orphan*/  SM501_MISC_TIMING ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  sm501_init_reg (struct sm501_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sm501_misc_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm501_set_clock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sm501_init_regs(struct sm501_devdata *sm,
			    struct sm501_initdata *init)
{
	sm501_misc_control(sm->dev,
			   init->misc_control.set,
			   init->misc_control.mask);

	sm501_init_reg(sm, SM501_MISC_TIMING, &init->misc_timing);
	sm501_init_reg(sm, SM501_GPIO31_0_CONTROL, &init->gpio_low);
	sm501_init_reg(sm, SM501_GPIO63_32_CONTROL, &init->gpio_high);

	if (init->m1xclk) {
		dev_info(sm->dev, "setting M1XCLK to %ld\n", init->m1xclk);
		sm501_set_clock(sm->dev, SM501_CLOCK_M1XCLK, init->m1xclk);
	}

	if (init->mclk) {
		dev_info(sm->dev, "setting MCLK to %ld\n", init->mclk);
		sm501_set_clock(sm->dev, SM501_CLOCK_MCLK, init->mclk);
	}

}