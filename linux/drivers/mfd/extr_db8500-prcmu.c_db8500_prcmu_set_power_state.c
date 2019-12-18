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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MB0H_POWER_STATE_TRANS ; 
 int MBOX_BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ PRCMU_AP_DEEP_IDLE ; 
 scalar_t__ PRCMU_AP_SLEEP ; 
 int /*<<< orphan*/  PRCM_MBOX_CPU_SET ; 
 int /*<<< orphan*/  PRCM_MBOX_CPU_VAL ; 
 scalar_t__ PRCM_MBOX_HEADER_REQ_MB0 ; 
 scalar_t__ PRCM_REQ_MB0_AP_PLL_STATE ; 
 scalar_t__ PRCM_REQ_MB0_AP_POWER_STATE ; 
 scalar_t__ PRCM_REQ_MB0_DO_NOT_WFI ; 
 scalar_t__ PRCM_REQ_MB0_ULP_CLOCK_STATE ; 
 int /*<<< orphan*/  cpu_relax () ; 
 TYPE_1__ mb0_transfer ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ tcdm_base ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

int db8500_prcmu_set_power_state(u8 state, bool keep_ulp_clk, bool keep_ap_pll)
{
	unsigned long flags;

	BUG_ON((state < PRCMU_AP_SLEEP) || (PRCMU_AP_DEEP_IDLE < state));

	spin_lock_irqsave(&mb0_transfer.lock, flags);

	while (readl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(0))
		cpu_relax();

	writeb(MB0H_POWER_STATE_TRANS, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB0));
	writeb(state, (tcdm_base + PRCM_REQ_MB0_AP_POWER_STATE));
	writeb((keep_ap_pll ? 1 : 0), (tcdm_base + PRCM_REQ_MB0_AP_PLL_STATE));
	writeb((keep_ulp_clk ? 1 : 0),
		(tcdm_base + PRCM_REQ_MB0_ULP_CLOCK_STATE));
	writeb(0, (tcdm_base + PRCM_REQ_MB0_DO_NOT_WFI));
	writel(MBOX_BIT(0), PRCM_MBOX_CPU_SET);

	spin_unlock_irqrestore(&mb0_transfer.lock, flags);

	return 0;
}