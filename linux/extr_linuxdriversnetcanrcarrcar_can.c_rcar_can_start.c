#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_3__ {int ctrlmode; int /*<<< orphan*/  state; } ;
struct rcar_can_priv {int ier; TYPE_2__* regs; TYPE_1__ can; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tfcr; int /*<<< orphan*/  rfcr; int /*<<< orphan*/  str; int /*<<< orphan*/  ctlr; int /*<<< orphan*/  eier; int /*<<< orphan*/  ecsr; int /*<<< orphan*/  ier; int /*<<< orphan*/  mier1; int /*<<< orphan*/ * fidcr; int /*<<< orphan*/  mkivlr1; int /*<<< orphan*/ * mkr_2_9; } ;

/* Variables and functions */
 int CAN_CTRLMODE_BERR_REPORTING ; 
 int /*<<< orphan*/  CAN_STATE_ERROR_ACTIVE ; 
 int MAX_STR_READS ; 
 int RCAR_CAN_CTLR_BOM_ENT ; 
 int RCAR_CAN_CTLR_CANM ; 
 int RCAR_CAN_CTLR_CANM_FORCE_RESET ; 
 int RCAR_CAN_CTLR_IDFM_MIXED ; 
 int RCAR_CAN_CTLR_MBM ; 
 int RCAR_CAN_CTLR_MLM ; 
 int RCAR_CAN_CTLR_SLPM ; 
 int RCAR_CAN_ECSR_EDPM ; 
 int RCAR_CAN_EIER_BEIE ; 
 int RCAR_CAN_EIER_BOEIE ; 
 int RCAR_CAN_EIER_EPIE ; 
 int RCAR_CAN_EIER_EWIE ; 
 int RCAR_CAN_EIER_OLIE ; 
 int RCAR_CAN_EIER_ORIE ; 
 int RCAR_CAN_FIDCR_IDE ; 
 int RCAR_CAN_FIDCR_RTR ; 
 int RCAR_CAN_IER_ERSIE ; 
 int RCAR_CAN_IER_RXFIE ; 
 int RCAR_CAN_IER_TXFIE ; 
 int RCAR_CAN_MIER1_RXFIE ; 
 int RCAR_CAN_MIER1_TXFIE ; 
 int RCAR_CAN_RFCR_RFE ; 
 int RCAR_CAN_STR_RSTST ; 
 int RCAR_CAN_TFCR_TFE ; 
 struct rcar_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rcar_can_set_bittiming (struct net_device*) ; 
 int readw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rcar_can_start(struct net_device *ndev)
{
	struct rcar_can_priv *priv = netdev_priv(ndev);
	u16 ctlr;
	int i;

	/* Set controller to known mode:
	 * - FIFO mailbox mode
	 * - accept all messages
	 * - overrun mode
	 * CAN is in sleep mode after MCU hardware or software reset.
	 */
	ctlr = readw(&priv->regs->ctlr);
	ctlr &= ~RCAR_CAN_CTLR_SLPM;
	writew(ctlr, &priv->regs->ctlr);
	/* Go to reset mode */
	ctlr |= RCAR_CAN_CTLR_CANM_FORCE_RESET;
	writew(ctlr, &priv->regs->ctlr);
	for (i = 0; i < MAX_STR_READS; i++) {
		if (readw(&priv->regs->str) & RCAR_CAN_STR_RSTST)
			break;
	}
	rcar_can_set_bittiming(ndev);
	ctlr |= RCAR_CAN_CTLR_IDFM_MIXED; /* Select mixed ID mode */
	ctlr |= RCAR_CAN_CTLR_BOM_ENT;	/* Entry to halt mode automatically */
					/* at bus-off */
	ctlr |= RCAR_CAN_CTLR_MBM;	/* Select FIFO mailbox mode */
	ctlr |= RCAR_CAN_CTLR_MLM;	/* Overrun mode */
	writew(ctlr, &priv->regs->ctlr);

	/* Accept all SID and EID */
	writel(0, &priv->regs->mkr_2_9[6]);
	writel(0, &priv->regs->mkr_2_9[7]);
	/* In FIFO mailbox mode, write "0" to bits 24 to 31 */
	writel(0, &priv->regs->mkivlr1);
	/* Accept all frames */
	writel(0, &priv->regs->fidcr[0]);
	writel(RCAR_CAN_FIDCR_IDE | RCAR_CAN_FIDCR_RTR, &priv->regs->fidcr[1]);
	/* Enable and configure FIFO mailbox interrupts */
	writel(RCAR_CAN_MIER1_RXFIE | RCAR_CAN_MIER1_TXFIE, &priv->regs->mier1);

	priv->ier = RCAR_CAN_IER_ERSIE | RCAR_CAN_IER_RXFIE |
		    RCAR_CAN_IER_TXFIE;
	writeb(priv->ier, &priv->regs->ier);

	/* Accumulate error codes */
	writeb(RCAR_CAN_ECSR_EDPM, &priv->regs->ecsr);
	/* Enable error interrupts */
	writeb(RCAR_CAN_EIER_EWIE | RCAR_CAN_EIER_EPIE | RCAR_CAN_EIER_BOEIE |
	       (priv->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING ?
	       RCAR_CAN_EIER_BEIE : 0) | RCAR_CAN_EIER_ORIE |
	       RCAR_CAN_EIER_OLIE, &priv->regs->eier);
	priv->can.state = CAN_STATE_ERROR_ACTIVE;

	/* Go to operation mode */
	writew(ctlr & ~RCAR_CAN_CTLR_CANM, &priv->regs->ctlr);
	for (i = 0; i < MAX_STR_READS; i++) {
		if (!(readw(&priv->regs->str) & RCAR_CAN_STR_RSTST))
			break;
	}
	/* Enable Rx and Tx FIFO */
	writeb(RCAR_CAN_RFCR_RFE, &priv->regs->rfcr);
	writeb(RCAR_CAN_TFCR_TFE, &priv->regs->tfcr);
}