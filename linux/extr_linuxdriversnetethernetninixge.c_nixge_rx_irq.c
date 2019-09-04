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
typedef  unsigned int u32 ;
struct nixge_priv {size_t rx_bd_ci; int /*<<< orphan*/  dma_err_tasklet; TYPE_1__* rx_bd_v; int /*<<< orphan*/  napi; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {unsigned int phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int XAXIDMA_IRQ_ALL_MASK ; 
 unsigned int XAXIDMA_IRQ_DELAY_MASK ; 
 unsigned int XAXIDMA_IRQ_ERROR_MASK ; 
 unsigned int XAXIDMA_IRQ_IOC_MASK ; 
 int /*<<< orphan*/  XAXIDMA_RX_CR_OFFSET ; 
 int /*<<< orphan*/  XAXIDMA_RX_SR_OFFSET ; 
 int /*<<< orphan*/  XAXIDMA_TX_CR_OFFSET ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct nixge_priv* netdev_priv (void*) ; 
 unsigned int nixge_dma_read_reg (struct nixge_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nixge_dma_write_reg (struct nixge_priv*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t nixge_rx_irq(int irq, void *_ndev)
{
	struct nixge_priv *priv = netdev_priv(_ndev);
	struct net_device *ndev = _ndev;
	unsigned int status;
	u32 cr;

	status = nixge_dma_read_reg(priv, XAXIDMA_RX_SR_OFFSET);
	if (status & (XAXIDMA_IRQ_IOC_MASK | XAXIDMA_IRQ_DELAY_MASK)) {
		/* Turn of IRQs because NAPI */
		nixge_dma_write_reg(priv, XAXIDMA_RX_SR_OFFSET, status);
		cr = nixge_dma_read_reg(priv, XAXIDMA_RX_CR_OFFSET);
		cr &= ~(XAXIDMA_IRQ_IOC_MASK | XAXIDMA_IRQ_DELAY_MASK);
		nixge_dma_write_reg(priv, XAXIDMA_RX_CR_OFFSET, cr);

		if (napi_schedule_prep(&priv->napi))
			__napi_schedule(&priv->napi);
		goto out;
	}
	if (!(status & XAXIDMA_IRQ_ALL_MASK)) {
		netdev_err(ndev, "No interrupts asserted in Rx path\n");
		return IRQ_NONE;
	}
	if (status & XAXIDMA_IRQ_ERROR_MASK) {
		netdev_err(ndev, "DMA Rx error 0x%x\n", status);
		netdev_err(ndev, "Current BD is at: 0x%x\n",
			   (priv->rx_bd_v[priv->rx_bd_ci]).phys);

		cr = nixge_dma_read_reg(priv, XAXIDMA_TX_CR_OFFSET);
		/* Disable coalesce, delay timer and error interrupts */
		cr &= (~XAXIDMA_IRQ_ALL_MASK);
		/* Finally write to the Tx channel control register */
		nixge_dma_write_reg(priv, XAXIDMA_TX_CR_OFFSET, cr);

		cr = nixge_dma_read_reg(priv, XAXIDMA_RX_CR_OFFSET);
		/* Disable coalesce, delay timer and error interrupts */
		cr &= (~XAXIDMA_IRQ_ALL_MASK);
		/* write to the Rx channel control register */
		nixge_dma_write_reg(priv, XAXIDMA_RX_CR_OFFSET, cr);

		tasklet_schedule(&priv->dma_err_tasklet);
		nixge_dma_write_reg(priv, XAXIDMA_RX_SR_OFFSET, status);
	}
out:
	return IRQ_HANDLED;
}