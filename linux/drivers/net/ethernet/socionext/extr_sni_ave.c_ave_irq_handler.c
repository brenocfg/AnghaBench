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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dropped; int /*<<< orphan*/  fifo_errors; } ;
struct ave_private {int /*<<< orphan*/  napi_tx; int /*<<< orphan*/  napi_rx; scalar_t__ base; TYPE_1__ stats_rx; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ AVE_GISR ; 
 int AVE_GI_PHY ; 
 int AVE_GI_RXDROP ; 
 int AVE_GI_RXERR ; 
 int AVE_GI_RXIINT ; 
 int AVE_GI_RXOVF ; 
 int AVE_GI_TX ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int ave_irq_disable_all (struct net_device*) ; 
 int /*<<< orphan*/  ave_irq_restore (struct net_device*,int) ; 
 int /*<<< orphan*/  ave_rxfifo_reset (struct net_device*) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct ave_private* netdev_priv (struct net_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t ave_irq_handler(int irq, void *netdev)
{
	struct net_device *ndev = (struct net_device *)netdev;
	struct ave_private *priv = netdev_priv(ndev);
	u32 gimr_val, gisr_val;

	gimr_val = ave_irq_disable_all(ndev);

	/* get interrupt status */
	gisr_val = readl(priv->base + AVE_GISR);

	/* PHY */
	if (gisr_val & AVE_GI_PHY)
		writel(AVE_GI_PHY, priv->base + AVE_GISR);

	/* check exceeding packet */
	if (gisr_val & AVE_GI_RXERR) {
		writel(AVE_GI_RXERR, priv->base + AVE_GISR);
		netdev_err(ndev, "receive a packet exceeding frame buffer\n");
	}

	gisr_val &= gimr_val;
	if (!gisr_val)
		goto exit_isr;

	/* RxFIFO overflow */
	if (gisr_val & AVE_GI_RXOVF) {
		priv->stats_rx.fifo_errors++;
		ave_rxfifo_reset(ndev);
		goto exit_isr;
	}

	/* Rx drop */
	if (gisr_val & AVE_GI_RXDROP) {
		priv->stats_rx.dropped++;
		writel(AVE_GI_RXDROP, priv->base + AVE_GISR);
	}

	/* Rx interval */
	if (gisr_val & AVE_GI_RXIINT) {
		napi_schedule(&priv->napi_rx);
		/* still force to disable Rx interrupt until NAPI finishes */
		gimr_val &= ~AVE_GI_RXIINT;
	}

	/* Tx completed */
	if (gisr_val & AVE_GI_TX) {
		napi_schedule(&priv->napi_tx);
		/* still force to disable Tx interrupt until NAPI finishes */
		gimr_val &= ~AVE_GI_TX;
	}

exit_isr:
	ave_irq_restore(ndev, gimr_val);

	return IRQ_HANDLED;
}