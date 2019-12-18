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
typedef  scalar_t__ u32 ;
struct sky2_port {int tx_ring_size; struct sky2_hw* hw; } ;
struct sky2_hw {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {scalar_t__ const tx_coalesce_usecs; scalar_t__ const rx_coalesce_usecs; scalar_t__ const rx_coalesce_usecs_irq; int tx_max_coalesced_frames; scalar_t__ rx_max_coalesced_frames; scalar_t__ rx_max_coalesced_frames_irq; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RX_MAX_PENDING ; 
 int /*<<< orphan*/  STAT_FIFO_ISR_WM ; 
 int /*<<< orphan*/  STAT_FIFO_WM ; 
 int /*<<< orphan*/  STAT_ISR_TIMER_CTRL ; 
 int /*<<< orphan*/  STAT_ISR_TIMER_INI ; 
 int /*<<< orphan*/  STAT_LEV_TIMER_CTRL ; 
 int /*<<< orphan*/  STAT_LEV_TIMER_INI ; 
 int /*<<< orphan*/  STAT_TX_IDX_TH ; 
 int /*<<< orphan*/  STAT_TX_TIMER_CTRL ; 
 int /*<<< orphan*/  STAT_TX_TIMER_INI ; 
 scalar_t__ TIM_START ; 
 scalar_t__ TIM_STOP ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 scalar_t__ sky2_clk2us (struct sky2_hw*,int) ; 
 int /*<<< orphan*/  sky2_us2clk (struct sky2_hw*,scalar_t__) ; 
 int /*<<< orphan*/  sky2_write16 (struct sky2_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sky2_set_coalesce(struct net_device *dev,
			     struct ethtool_coalesce *ecmd)
{
	struct sky2_port *sky2 = netdev_priv(dev);
	struct sky2_hw *hw = sky2->hw;
	const u32 tmax = sky2_clk2us(hw, 0x0ffffff);

	if (ecmd->tx_coalesce_usecs > tmax ||
	    ecmd->rx_coalesce_usecs > tmax ||
	    ecmd->rx_coalesce_usecs_irq > tmax)
		return -EINVAL;

	if (ecmd->tx_max_coalesced_frames >= sky2->tx_ring_size-1)
		return -EINVAL;
	if (ecmd->rx_max_coalesced_frames > RX_MAX_PENDING)
		return -EINVAL;
	if (ecmd->rx_max_coalesced_frames_irq > RX_MAX_PENDING)
		return -EINVAL;

	if (ecmd->tx_coalesce_usecs == 0)
		sky2_write8(hw, STAT_TX_TIMER_CTRL, TIM_STOP);
	else {
		sky2_write32(hw, STAT_TX_TIMER_INI,
			     sky2_us2clk(hw, ecmd->tx_coalesce_usecs));
		sky2_write8(hw, STAT_TX_TIMER_CTRL, TIM_START);
	}
	sky2_write16(hw, STAT_TX_IDX_TH, ecmd->tx_max_coalesced_frames);

	if (ecmd->rx_coalesce_usecs == 0)
		sky2_write8(hw, STAT_LEV_TIMER_CTRL, TIM_STOP);
	else {
		sky2_write32(hw, STAT_LEV_TIMER_INI,
			     sky2_us2clk(hw, ecmd->rx_coalesce_usecs));
		sky2_write8(hw, STAT_LEV_TIMER_CTRL, TIM_START);
	}
	sky2_write8(hw, STAT_FIFO_WM, ecmd->rx_max_coalesced_frames);

	if (ecmd->rx_coalesce_usecs_irq == 0)
		sky2_write8(hw, STAT_ISR_TIMER_CTRL, TIM_STOP);
	else {
		sky2_write32(hw, STAT_ISR_TIMER_INI,
			     sky2_us2clk(hw, ecmd->rx_coalesce_usecs_irq));
		sky2_write8(hw, STAT_ISR_TIMER_CTRL, TIM_START);
	}
	sky2_write8(hw, STAT_FIFO_ISR_WM, ecmd->rx_max_coalesced_frames_irq);
	return 0;
}