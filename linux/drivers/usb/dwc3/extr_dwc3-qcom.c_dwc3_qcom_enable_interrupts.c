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
struct dwc3_qcom {scalar_t__ ss_phy_irq; scalar_t__ dm_hs_phy_irq; scalar_t__ dp_hs_phy_irq; scalar_t__ hs_phy_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (scalar_t__) ; 
 int /*<<< orphan*/  enable_irq_wake (scalar_t__) ; 

__attribute__((used)) static void dwc3_qcom_enable_interrupts(struct dwc3_qcom *qcom)
{
	if (qcom->hs_phy_irq) {
		enable_irq(qcom->hs_phy_irq);
		enable_irq_wake(qcom->hs_phy_irq);
	}

	if (qcom->dp_hs_phy_irq) {
		enable_irq(qcom->dp_hs_phy_irq);
		enable_irq_wake(qcom->dp_hs_phy_irq);
	}

	if (qcom->dm_hs_phy_irq) {
		enable_irq(qcom->dm_hs_phy_irq);
		enable_irq_wake(qcom->dm_hs_phy_irq);
	}

	if (qcom->ss_phy_irq) {
		enable_irq(qcom->ss_phy_irq);
		enable_irq_wake(qcom->ss_phy_irq);
	}
}