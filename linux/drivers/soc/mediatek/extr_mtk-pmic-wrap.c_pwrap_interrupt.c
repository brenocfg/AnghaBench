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
typedef  int /*<<< orphan*/  u32 ;
struct pmic_wrapper {int /*<<< orphan*/  dev; TYPE_1__* master; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 scalar_t__ HAS_CAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  PWRAP_CAP_INT1_EN ; 
 int /*<<< orphan*/  PWRAP_INT1_CLR ; 
 int /*<<< orphan*/  PWRAP_INT1_FLG ; 
 int /*<<< orphan*/  PWRAP_INT_CLR ; 
 int /*<<< orphan*/  PWRAP_INT_FLG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrap_readl (struct pmic_wrapper*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrap_writel (struct pmic_wrapper*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t pwrap_interrupt(int irqno, void *dev_id)
{
	u32 rdata;
	struct pmic_wrapper *wrp = dev_id;

	rdata = pwrap_readl(wrp, PWRAP_INT_FLG);
	dev_err(wrp->dev, "unexpected interrupt int=0x%x\n", rdata);
	pwrap_writel(wrp, 0xffffffff, PWRAP_INT_CLR);

	if (HAS_CAP(wrp->master->caps, PWRAP_CAP_INT1_EN)) {
		rdata = pwrap_readl(wrp, PWRAP_INT1_FLG);
		dev_err(wrp->dev, "unexpected interrupt int1=0x%x\n", rdata);
		pwrap_writel(wrp, 0xffffffff, PWRAP_INT1_CLR);
	}

	return IRQ_HANDLED;
}