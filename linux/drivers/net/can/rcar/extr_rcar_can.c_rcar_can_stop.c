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
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct rcar_can_priv {TYPE_2__ can; TYPE_1__* regs; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ctlr; int /*<<< orphan*/  eier; int /*<<< orphan*/  ier; int /*<<< orphan*/  mier1; int /*<<< orphan*/  mier0; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 int MAX_STR_READS ; 
 int RCAR_CAN_CTLR_CANM_FORCE_RESET ; 
 int RCAR_CAN_CTLR_SLPM ; 
 int RCAR_CAN_STR_RSTST ; 
 struct rcar_can_priv* netdev_priv (struct net_device*) ; 
 int readw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rcar_can_stop(struct net_device *ndev)
{
	struct rcar_can_priv *priv = netdev_priv(ndev);
	u16 ctlr;
	int i;

	/* Go to (force) reset mode */
	ctlr = readw(&priv->regs->ctlr);
	ctlr |= RCAR_CAN_CTLR_CANM_FORCE_RESET;
	writew(ctlr, &priv->regs->ctlr);
	for (i = 0; i < MAX_STR_READS; i++) {
		if (readw(&priv->regs->str) & RCAR_CAN_STR_RSTST)
			break;
	}
	writel(0, &priv->regs->mier0);
	writel(0, &priv->regs->mier1);
	writeb(0, &priv->regs->ier);
	writeb(0, &priv->regs->eier);
	/* Go to sleep mode */
	ctlr |= RCAR_CAN_CTLR_SLPM;
	writew(ctlr, &priv->regs->ctlr);
	priv->can.state = CAN_STATE_STOPPED;
}