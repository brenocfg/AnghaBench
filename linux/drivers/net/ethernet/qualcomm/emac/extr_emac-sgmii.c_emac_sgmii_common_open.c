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
struct emac_sgmii {scalar_t__ irq; scalar_t__ base; } ;
struct emac_adapter {int /*<<< orphan*/  netdev; struct emac_sgmii phy; } ;

/* Variables and functions */
 scalar_t__ EMAC_SGMII_PHY_INTERRUPT_MASK ; 
 int /*<<< orphan*/  emac_sgmii_interrupt ; 
 int emac_sgmii_irq_clear (struct emac_adapter*,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct emac_adapter*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int emac_sgmii_common_open(struct emac_adapter *adpt)
{
	struct emac_sgmii *sgmii = &adpt->phy;
	int ret;

	if (sgmii->irq) {
		/* Make sure interrupts are cleared and disabled first */
		ret = emac_sgmii_irq_clear(adpt, 0xff);
		if (ret)
			return ret;
		writel(0, sgmii->base + EMAC_SGMII_PHY_INTERRUPT_MASK);

		ret = request_irq(sgmii->irq, emac_sgmii_interrupt, 0,
				  "emac-sgmii", adpt);
		if (ret) {
			netdev_err(adpt->netdev,
				   "could not register handler for internal PHY\n");
			return ret;
		}
	}

	return 0;
}