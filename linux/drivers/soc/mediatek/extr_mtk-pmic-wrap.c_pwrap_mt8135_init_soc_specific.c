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
struct pmic_wrapper {int /*<<< orphan*/  dev; TYPE_1__* slave; scalar_t__ bridge_base; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dew_regs; } ;

/* Variables and functions */
 int EFAULT ; 
 size_t PWRAP_DEW_EVENT_OUT_EN ; 
 size_t PWRAP_DEW_EVENT_SRC_EN ; 
 int /*<<< orphan*/  PWRAP_EVENT_DST_EN ; 
 int /*<<< orphan*/  PWRAP_EVENT_IN_EN ; 
 scalar_t__ PWRAP_MT8135_BRIDGE_INT_EN ; 
 scalar_t__ PWRAP_MT8135_BRIDGE_IORD_ARB_EN ; 
 scalar_t__ PWRAP_MT8135_BRIDGE_TIMER_EN ; 
 scalar_t__ PWRAP_MT8135_BRIDGE_WACS3_EN ; 
 scalar_t__ PWRAP_MT8135_BRIDGE_WACS4_EN ; 
 scalar_t__ PWRAP_MT8135_BRIDGE_WDT_SRC_EN ; 
 scalar_t__ PWRAP_MT8135_BRIDGE_WDT_UNIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pwrap_write (struct pmic_wrapper*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pwrap_writel (struct pmic_wrapper*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int pwrap_mt8135_init_soc_specific(struct pmic_wrapper *wrp)
{
	/* enable pwrap events and pwrap bridge in AP side */
	pwrap_writel(wrp, 0x1, PWRAP_EVENT_IN_EN);
	pwrap_writel(wrp, 0xffff, PWRAP_EVENT_DST_EN);
	writel(0x7f, wrp->bridge_base + PWRAP_MT8135_BRIDGE_IORD_ARB_EN);
	writel(0x1, wrp->bridge_base + PWRAP_MT8135_BRIDGE_WACS3_EN);
	writel(0x1, wrp->bridge_base + PWRAP_MT8135_BRIDGE_WACS4_EN);
	writel(0x1, wrp->bridge_base + PWRAP_MT8135_BRIDGE_WDT_UNIT);
	writel(0xffff, wrp->bridge_base + PWRAP_MT8135_BRIDGE_WDT_SRC_EN);
	writel(0x1, wrp->bridge_base + PWRAP_MT8135_BRIDGE_TIMER_EN);
	writel(0x7ff, wrp->bridge_base + PWRAP_MT8135_BRIDGE_INT_EN);

	/* enable PMIC event out and sources */
	if (pwrap_write(wrp, wrp->slave->dew_regs[PWRAP_DEW_EVENT_OUT_EN],
			0x1) ||
	    pwrap_write(wrp, wrp->slave->dew_regs[PWRAP_DEW_EVENT_SRC_EN],
			0xffff)) {
		dev_err(wrp->dev, "enable dewrap fail\n");
		return -EFAULT;
	}

	return 0;
}