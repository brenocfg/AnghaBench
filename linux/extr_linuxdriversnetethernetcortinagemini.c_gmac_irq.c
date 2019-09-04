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
struct net_device {int dev_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_fifo_errors; } ;
struct gemini_ethernet_port {int /*<<< orphan*/  ir_stats_syncp; TYPE_1__ stats; int /*<<< orphan*/  rx_coalesce_timer; int /*<<< orphan*/  rx_coalesce_nsecs; int /*<<< orphan*/  napi; struct gemini_ethernet* geth; } ;
struct gemini_ethernet {int /*<<< orphan*/  irq_lock; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DEFAULT_Q0_INT_BIT ; 
 scalar_t__ GLOBAL_INTERRUPT_STATUS_4_REG ; 
 int GMAC0_IRQ0_2 ; 
 int GMAC0_IRQ0_TXQ0_INTS ; 
 int GMAC0_MIB_INT_BIT ; 
 int GMAC0_RXDERR_INT_BIT ; 
 int GMAC0_RX_OVERRUN_INT_BIT ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  gmac_dump_dma_state (struct net_device*) ; 
 int /*<<< orphan*/  gmac_enable_irq (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmac_enable_rx_irq (struct net_device*,int /*<<< orphan*/ ) ; 
 int gmac_get_intr_flags (struct net_device*,int) ; 
 int /*<<< orphan*/  gmac_tx_irq (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmac_update_hw_stats (struct net_device*) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct gemini_ethernet_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t gmac_irq(int irq, void *data)
{
	struct gemini_ethernet_port *port;
	struct net_device *netdev = data;
	struct gemini_ethernet *geth;
	u32 val, orr = 0;

	port = netdev_priv(netdev);
	geth = port->geth;

	val = gmac_get_intr_flags(netdev, 0);
	orr |= val;

	if (val & (GMAC0_IRQ0_2 << (netdev->dev_id * 2))) {
		/* Oh, crap */
		netdev_err(netdev, "hw failure/sw bug\n");
		gmac_dump_dma_state(netdev);

		/* don't know how to recover, just reduce losses */
		gmac_enable_irq(netdev, 0);
		return IRQ_HANDLED;
	}

	if (val & (GMAC0_IRQ0_TXQ0_INTS << (netdev->dev_id * 6)))
		gmac_tx_irq(netdev, 0);

	val = gmac_get_intr_flags(netdev, 1);
	orr |= val;

	if (val & (DEFAULT_Q0_INT_BIT << netdev->dev_id)) {
		gmac_enable_rx_irq(netdev, 0);

		if (!port->rx_coalesce_nsecs) {
			napi_schedule(&port->napi);
		} else {
			ktime_t ktime;

			ktime = ktime_set(0, port->rx_coalesce_nsecs);
			hrtimer_start(&port->rx_coalesce_timer, ktime,
				      HRTIMER_MODE_REL);
		}
	}

	val = gmac_get_intr_flags(netdev, 4);
	orr |= val;

	if (val & (GMAC0_MIB_INT_BIT << (netdev->dev_id * 8)))
		gmac_update_hw_stats(netdev);

	if (val & (GMAC0_RX_OVERRUN_INT_BIT << (netdev->dev_id * 8))) {
		writel(GMAC0_RXDERR_INT_BIT << (netdev->dev_id * 8),
		       geth->base + GLOBAL_INTERRUPT_STATUS_4_REG);

		spin_lock(&geth->irq_lock);
		u64_stats_update_begin(&port->ir_stats_syncp);
		++port->stats.rx_fifo_errors;
		u64_stats_update_end(&port->ir_stats_syncp);
		spin_unlock(&geth->irq_lock);
	}

	return orr ? IRQ_HANDLED : IRQ_NONE;
}