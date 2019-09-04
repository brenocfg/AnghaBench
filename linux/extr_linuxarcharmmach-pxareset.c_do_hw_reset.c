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

/* Variables and functions */
 int /*<<< orphan*/  MDREFR ; 
 scalar_t__ MDREFR_SLFRSH ; 
 int /*<<< orphan*/  OSCR ; 
 int /*<<< orphan*/  OSMR3 ; 
 int /*<<< orphan*/  OSSR ; 
 scalar_t__ OSSR_M3 ; 
 int /*<<< orphan*/  OWER ; 
 scalar_t__ OWER_WME ; 
 scalar_t__ readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_hw_reset(void)
{
	/* Initialize the watchdog and let it fire */
	writel_relaxed(OWER_WME, OWER);
	writel_relaxed(OSSR_M3, OSSR);
	/* ... in 100 ms */
	writel_relaxed(readl_relaxed(OSCR) + 368640, OSMR3);
	/*
	 * SDRAM hangs on watchdog reset on Marvell PXA270 (erratum 71)
	 * we put SDRAM into self-refresh to prevent that
	 */
	while (1)
		writel_relaxed(MDREFR_SLFRSH, MDREFR);
}