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
struct wl1271 {int /*<<< orphan*/ * ptable; } ;

/* Variables and functions */
 size_t PART_BOOT ; 
 int /*<<< orphan*/  REG_INTERRUPT_MASK ; 
 int /*<<< orphan*/  WELP_ARM_COMMAND_VAL ; 
 int /*<<< orphan*/  WL1271_ACX_INTR_ALL ; 
 int /*<<< orphan*/  WL18XX_WELP_ARM_COMMAND ; 
 int /*<<< orphan*/  udelay (int) ; 
 int wl18xx_boot_soft_reset (struct wl1271*) ; 
 int wl18xx_set_clk (struct wl1271*) ; 
 int wlcore_set_partition (struct wl1271*,int /*<<< orphan*/ *) ; 
 int wlcore_write32 (struct wl1271*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wlcore_write_reg (struct wl1271*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wl18xx_pre_boot(struct wl1271 *wl)
{
	int ret;

	ret = wl18xx_set_clk(wl);
	if (ret < 0)
		goto out;

	/* Continue the ELP wake up sequence */
	ret = wlcore_write32(wl, WL18XX_WELP_ARM_COMMAND, WELP_ARM_COMMAND_VAL);
	if (ret < 0)
		goto out;

	udelay(500);

	ret = wlcore_set_partition(wl, &wl->ptable[PART_BOOT]);
	if (ret < 0)
		goto out;

	/* Disable interrupts */
	ret = wlcore_write_reg(wl, REG_INTERRUPT_MASK, WL1271_ACX_INTR_ALL);
	if (ret < 0)
		goto out;

	ret = wl18xx_boot_soft_reset(wl);

out:
	return ret;
}