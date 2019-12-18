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
struct temac_local {unsigned int (* dma_in ) (struct temac_local*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ndev; int /*<<< orphan*/  (* dma_out ) (struct temac_local*,int /*<<< orphan*/ ,unsigned int) ;} ;
struct net_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int IRQ_COAL ; 
 unsigned int IRQ_DLY ; 
 unsigned int IRQ_DMAERR ; 
 unsigned int IRQ_ERR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  RX_CHNL_STS ; 
 int /*<<< orphan*/  RX_IRQ_REG ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ *,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ll_temac_recv (int /*<<< orphan*/ ) ; 
 struct temac_local* netdev_priv (struct net_device*) ; 
 unsigned int stub1 (struct temac_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct temac_local*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int stub3 (struct temac_local*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ll_temac_rx_irq(int irq, void *_ndev)
{
	struct net_device *ndev = _ndev;
	struct temac_local *lp = netdev_priv(ndev);
	unsigned int status;

	/* Read and clear the status registers */
	status = lp->dma_in(lp, RX_IRQ_REG);
	lp->dma_out(lp, RX_IRQ_REG, status);

	if (status & (IRQ_COAL | IRQ_DLY))
		ll_temac_recv(lp->ndev);
	if (status & (IRQ_ERR | IRQ_DMAERR))
		dev_err_ratelimited(&ndev->dev,
				    "RX error 0x%x RX_CHNL_STS=0x%08x\n",
				    status, lp->dma_in(lp, RX_CHNL_STS));

	return IRQ_HANDLED;
}