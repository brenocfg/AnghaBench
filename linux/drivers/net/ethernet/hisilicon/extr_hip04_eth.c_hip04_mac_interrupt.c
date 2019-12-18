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
typedef  int u32 ;
struct net_device_stats {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; } ;
struct net_device {struct net_device_stats stats; } ;
struct hip04_priv {int reg_inten; int /*<<< orphan*/  napi; int /*<<< orphan*/  tx_coalesce_timer; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DEF_INT_ERR ; 
 int DEF_INT_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ PPE_INTEN ; 
 scalar_t__ PPE_INTSTS ; 
 scalar_t__ PPE_RINT ; 
 int RCV_DROP ; 
 int RCV_INT ; 
 int RCV_NOBUF ; 
 int TX_DROP ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct hip04_priv* netdev_priv (struct net_device*) ; 
 int readl_relaxed (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t hip04_mac_interrupt(int irq, void *dev_id)
{
	struct net_device *ndev = (struct net_device *)dev_id;
	struct hip04_priv *priv = netdev_priv(ndev);
	struct net_device_stats *stats = &ndev->stats;
	u32 ists = readl_relaxed(priv->base + PPE_INTSTS);

	if (!ists)
		return IRQ_NONE;

	writel_relaxed(DEF_INT_MASK, priv->base + PPE_RINT);

	if (unlikely(ists & DEF_INT_ERR)) {
		if (ists & (RCV_NOBUF | RCV_DROP)) {
			stats->rx_errors++;
			stats->rx_dropped++;
			netdev_err(ndev, "rx drop\n");
		}
		if (ists & TX_DROP) {
			stats->tx_dropped++;
			netdev_err(ndev, "tx drop\n");
		}
	}

	if (ists & RCV_INT && napi_schedule_prep(&priv->napi)) {
		/* disable rx interrupt */
		priv->reg_inten &= ~(RCV_INT);
		writel_relaxed(DEF_INT_MASK & ~RCV_INT, priv->base + PPE_INTEN);
		hrtimer_cancel(&priv->tx_coalesce_timer);
		__napi_schedule(&priv->napi);
	}

	return IRQ_HANDLED;
}