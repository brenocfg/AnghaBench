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
struct emac_sgmii {int /*<<< orphan*/  irq; scalar_t__ base; } ;
struct emac_adapter {struct emac_sgmii phy; } ;

/* Variables and functions */
 scalar_t__ EMAC_SGMII_PHY_INTERRUPT_MASK ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct emac_adapter*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void emac_sgmii_common_close(struct emac_adapter *adpt)
{
	struct emac_sgmii *sgmii = &adpt->phy;

	/* Make sure interrupts are disabled */
	writel(0, sgmii->base + EMAC_SGMII_PHY_INTERRUPT_MASK);
	free_irq(sgmii->irq, adpt);
}