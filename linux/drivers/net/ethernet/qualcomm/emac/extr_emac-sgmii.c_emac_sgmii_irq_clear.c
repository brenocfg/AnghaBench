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
typedef  int u8 ;
struct emac_sgmii {scalar_t__ base; } ;
struct emac_adapter {TYPE_1__* netdev; struct emac_sgmii phy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ EMAC_SGMII_PHY_INTERRUPT_CLEAR ; 
 scalar_t__ EMAC_SGMII_PHY_INTERRUPT_STATUS ; 
 scalar_t__ EMAC_SGMII_PHY_IRQ_CMD ; 
 int IRQ_GLOBAL_CLEAR ; 
 int /*<<< orphan*/  SGMII_PHY_IRQ_CLR_WAIT_TIME ; 
 int /*<<< orphan*/  net_err_ratelimited (char*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ readl_poll_timeout_atomic (scalar_t__,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int emac_sgmii_irq_clear(struct emac_adapter *adpt, u8 irq_bits)
{
	struct emac_sgmii *phy = &adpt->phy;
	u8 status;

	writel_relaxed(irq_bits, phy->base + EMAC_SGMII_PHY_INTERRUPT_CLEAR);
	writel_relaxed(IRQ_GLOBAL_CLEAR, phy->base + EMAC_SGMII_PHY_IRQ_CMD);
	/* Ensure interrupt clear command is written to HW */
	wmb();

	/* After set the IRQ_GLOBAL_CLEAR bit, the status clearing must
	 * be confirmed before clearing the bits in other registers.
	 * It takes a few cycles for hw to clear the interrupt status.
	 */
	if (readl_poll_timeout_atomic(phy->base +
				      EMAC_SGMII_PHY_INTERRUPT_STATUS,
				      status, !(status & irq_bits), 1,
				      SGMII_PHY_IRQ_CLR_WAIT_TIME)) {
		net_err_ratelimited("%s: failed to clear SGMII irq: status:0x%x bits:0x%x\n",
				    adpt->netdev->name, status, irq_bits);
		return -EIO;
	}

	/* Finalize clearing procedure */
	writel_relaxed(0, phy->base + EMAC_SGMII_PHY_IRQ_CMD);
	writel_relaxed(0, phy->base + EMAC_SGMII_PHY_INTERRUPT_CLEAR);

	/* Ensure that clearing procedure finalization is written to HW */
	wmb();

	return 0;
}