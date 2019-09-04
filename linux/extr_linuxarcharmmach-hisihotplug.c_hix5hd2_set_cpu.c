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

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int CRG20_CPU1_RESET ; 
 scalar_t__ HIX5HD2_PERI_CRG20 ; 
 scalar_t__ HIX5HD2_PERI_PMC0 ; 
 int PMC0_CPU1_PMC_ENABLE ; 
 int PMC0_CPU1_POWERDOWN ; 
 int PMC0_CPU1_WAIT_MTCOMS_ACK ; 
 scalar_t__ ctrl_base ; 
 int /*<<< orphan*/  hix5hd2_hotplug_init () ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

void hix5hd2_set_cpu(int cpu, bool enable)
{
	u32 val = 0;

	if (!ctrl_base)
		if (!hix5hd2_hotplug_init())
			BUG();

	if (enable) {
		/* power on cpu1 */
		val = readl_relaxed(ctrl_base + HIX5HD2_PERI_PMC0);
		val &= ~(PMC0_CPU1_WAIT_MTCOMS_ACK | PMC0_CPU1_POWERDOWN);
		val |= PMC0_CPU1_PMC_ENABLE;
		writel_relaxed(val, ctrl_base + HIX5HD2_PERI_PMC0);
		/* unreset */
		val = readl_relaxed(ctrl_base + HIX5HD2_PERI_CRG20);
		val &= ~CRG20_CPU1_RESET;
		writel_relaxed(val, ctrl_base + HIX5HD2_PERI_CRG20);
	} else {
		/* power down cpu1 */
		val = readl_relaxed(ctrl_base + HIX5HD2_PERI_PMC0);
		val |= PMC0_CPU1_PMC_ENABLE | PMC0_CPU1_POWERDOWN;
		val &= ~PMC0_CPU1_WAIT_MTCOMS_ACK;
		writel_relaxed(val, ctrl_base + HIX5HD2_PERI_PMC0);

		/* reset */
		val = readl_relaxed(ctrl_base + HIX5HD2_PERI_CRG20);
		val |= CRG20_CPU1_RESET;
		writel_relaxed(val, ctrl_base + HIX5HD2_PERI_CRG20);
	}
}