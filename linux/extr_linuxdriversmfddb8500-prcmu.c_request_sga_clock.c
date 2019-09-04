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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  PRCM_CGATING_BYPASS ; 
 int PRCM_CGATING_BYPASS_ICN2 ; 
 int readl (int /*<<< orphan*/ ) ; 
 int request_clock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int request_sga_clock(u8 clock, bool enable)
{
	u32 val;
	int ret;

	if (enable) {
		val = readl(PRCM_CGATING_BYPASS);
		writel(val | PRCM_CGATING_BYPASS_ICN2, PRCM_CGATING_BYPASS);
	}

	ret = request_clock(clock, enable);

	if (!ret && !enable) {
		val = readl(PRCM_CGATING_BYPASS);
		writel(val & ~PRCM_CGATING_BYPASS_ICN2, PRCM_CGATING_BYPASS);
	}

	return ret;
}