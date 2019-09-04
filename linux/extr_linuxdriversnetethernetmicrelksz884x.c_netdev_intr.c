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
typedef  int uint ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  rx_fifo_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct ksz_port {int dummy; } ;
struct ksz_hw {int intr_mask; scalar_t__ io; int /*<<< orphan*/  features; } ;
struct dev_priv {struct ksz_port port; struct dev_info* adapter; } ;
struct dev_info {int /*<<< orphan*/  hwlock; int /*<<< orphan*/  rx_tasklet; int /*<<< orphan*/  tx_tasklet; struct ksz_hw hw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DMA_TX_ENABLE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int KS884X_INT_PHY ; 
 int KS884X_INT_RX ; 
 int KS884X_INT_RX_OVERRUN ; 
 int KS884X_INT_RX_STOPPED ; 
 int KS884X_INT_TX_MASK ; 
 int KS884X_INT_TX_STOPPED ; 
 scalar_t__ KS_DMA_TX_CTRL ; 
 int /*<<< orphan*/  LINK_INT_WORKING ; 
 int /*<<< orphan*/  handle_rx_stop (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_ack_intr (struct ksz_hw*,int) ; 
 int /*<<< orphan*/  hw_dis_intr_bit (struct ksz_hw*,int) ; 
 int /*<<< orphan*/  hw_ena_intr (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_read_intr (struct ksz_hw*,int*) ; 
 int /*<<< orphan*/  hw_resume_rx (struct ksz_hw*) ; 
 scalar_t__ likely (int) ; 
 struct dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  port_get_link_speed (struct ksz_port*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t netdev_intr(int irq, void *dev_id)
{
	uint int_enable = 0;
	struct net_device *dev = (struct net_device *) dev_id;
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;

	spin_lock(&hw_priv->hwlock);

	hw_read_intr(hw, &int_enable);

	/* Not our interrupt! */
	if (!int_enable) {
		spin_unlock(&hw_priv->hwlock);
		return IRQ_NONE;
	}

	do {
		hw_ack_intr(hw, int_enable);
		int_enable &= hw->intr_mask;

		if (unlikely(int_enable & KS884X_INT_TX_MASK)) {
			hw_dis_intr_bit(hw, KS884X_INT_TX_MASK);
			tasklet_schedule(&hw_priv->tx_tasklet);
		}

		if (likely(int_enable & KS884X_INT_RX)) {
			hw_dis_intr_bit(hw, KS884X_INT_RX);
			tasklet_schedule(&hw_priv->rx_tasklet);
		}

		if (unlikely(int_enable & KS884X_INT_RX_OVERRUN)) {
			dev->stats.rx_fifo_errors++;
			hw_resume_rx(hw);
		}

		if (unlikely(int_enable & KS884X_INT_PHY)) {
			struct ksz_port *port = &priv->port;

			hw->features |= LINK_INT_WORKING;
			port_get_link_speed(port);
		}

		if (unlikely(int_enable & KS884X_INT_RX_STOPPED)) {
			handle_rx_stop(hw);
			break;
		}

		if (unlikely(int_enable & KS884X_INT_TX_STOPPED)) {
			u32 data;

			hw->intr_mask &= ~KS884X_INT_TX_STOPPED;
			pr_info("Tx stopped\n");
			data = readl(hw->io + KS_DMA_TX_CTRL);
			if (!(data & DMA_TX_ENABLE))
				pr_info("Tx disabled\n");
			break;
		}
	} while (0);

	hw_ena_intr(hw);

	spin_unlock(&hw_priv->hwlock);

	return IRQ_HANDLED;
}