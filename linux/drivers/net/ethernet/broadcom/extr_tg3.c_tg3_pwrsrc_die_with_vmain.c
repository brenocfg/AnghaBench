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
typedef  int u32 ;
struct tg3 {int grc_local_ctrl; } ;

/* Variables and functions */
 scalar_t__ ASIC_REV_5700 ; 
 scalar_t__ ASIC_REV_5701 ; 
 int GRC_LCLCTRL_GPIO_OE1 ; 
 int GRC_LCLCTRL_GPIO_OUTPUT1 ; 
 int /*<<< orphan*/  GRC_LOCAL_CTRL ; 
 int /*<<< orphan*/  IS_NIC ; 
 int /*<<< orphan*/  TG3_GRC_LCLCTL_PWRSW_DELAY ; 
 scalar_t__ tg3_asic_rev (struct tg3*) ; 
 int /*<<< orphan*/  tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32_wait_f (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_pwrsrc_die_with_vmain(struct tg3 *tp)
{
	u32 grc_local_ctrl;

	if (!tg3_flag(tp, IS_NIC) ||
	    tg3_asic_rev(tp) == ASIC_REV_5700 ||
	    tg3_asic_rev(tp) == ASIC_REV_5701)
		return;

	grc_local_ctrl = tp->grc_local_ctrl | GRC_LCLCTRL_GPIO_OE1;

	tw32_wait_f(GRC_LOCAL_CTRL,
		    grc_local_ctrl | GRC_LCLCTRL_GPIO_OUTPUT1,
		    TG3_GRC_LCLCTL_PWRSW_DELAY);

	tw32_wait_f(GRC_LOCAL_CTRL,
		    grc_local_ctrl,
		    TG3_GRC_LCLCTL_PWRSW_DELAY);

	tw32_wait_f(GRC_LOCAL_CTRL,
		    grc_local_ctrl | GRC_LCLCTRL_GPIO_OUTPUT1,
		    TG3_GRC_LCLCTL_PWRSW_DELAY);
}