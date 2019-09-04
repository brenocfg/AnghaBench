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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM63XX_RESET_ENETSW ; 
 scalar_t__ BCMCPU_IS_6328 () ; 
 scalar_t__ BCMCPU_IS_6362 () ; 
 scalar_t__ BCMCPU_IS_6368 () ; 
 int /*<<< orphan*/  CKCTL_6328_ROBOSW_EN ; 
 int /*<<< orphan*/  CKCTL_6362_ROBOSW_EN ; 
 int /*<<< orphan*/  CKCTL_6368_ROBOSW_EN ; 
 int /*<<< orphan*/  bcm63xx_core_set_reset (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcm_hwclock_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_disable_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_enable_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_swpkt_sar ; 
 int /*<<< orphan*/  clk_swpkt_usb ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void enetsw_set(struct clk *clk, int enable)
{
	if (BCMCPU_IS_6328()) {
		bcm_hwclock_set(CKCTL_6328_ROBOSW_EN, enable);
	} else if (BCMCPU_IS_6362()) {
		bcm_hwclock_set(CKCTL_6362_ROBOSW_EN, enable);
	} else if (BCMCPU_IS_6368()) {
		if (enable) {
			clk_enable_unlocked(&clk_swpkt_sar);
			clk_enable_unlocked(&clk_swpkt_usb);
		} else {
			clk_disable_unlocked(&clk_swpkt_usb);
			clk_disable_unlocked(&clk_swpkt_sar);
		}
		bcm_hwclock_set(CKCTL_6368_ROBOSW_EN, enable);
	} else {
		return;
	}

	if (enable) {
		/* reset switch core afer clock change */
		bcm63xx_core_set_reset(BCM63XX_RESET_ENETSW, 1);
		msleep(10);
		bcm63xx_core_set_reset(BCM63XX_RESET_ENETSW, 0);
		msleep(10);
	}
}