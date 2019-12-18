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
typedef  int /*<<< orphan*/  u32 ;
struct sky2_port {struct sky2_hw* hw; } ;
struct sky2_hw {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {scalar_t__ rx_max_coalesced_frames_irq; void* rx_coalesce_usecs_irq; scalar_t__ rx_max_coalesced_frames; void* rx_coalesce_usecs; int /*<<< orphan*/  tx_max_coalesced_frames; void* tx_coalesce_usecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAT_FIFO_ISR_WM ; 
 int /*<<< orphan*/  STAT_FIFO_WM ; 
 int /*<<< orphan*/  STAT_ISR_TIMER_CTRL ; 
 int /*<<< orphan*/  STAT_ISR_TIMER_INI ; 
 int /*<<< orphan*/  STAT_LEV_TIMER_CTRL ; 
 int /*<<< orphan*/  STAT_LEV_TIMER_INI ; 
 int /*<<< orphan*/  STAT_TX_IDX_TH ; 
 int /*<<< orphan*/  STAT_TX_TIMER_CTRL ; 
 int /*<<< orphan*/  STAT_TX_TIMER_INI ; 
 scalar_t__ TIM_STOP ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 void* sky2_clk2us (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_read16 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_read32 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ sky2_read8 (struct sky2_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sky2_get_coalesce(struct net_device *dev,
			     struct ethtool_coalesce *ecmd)
{
	struct sky2_port *sky2 = netdev_priv(dev);
	struct sky2_hw *hw = sky2->hw;

	if (sky2_read8(hw, STAT_TX_TIMER_CTRL) == TIM_STOP)
		ecmd->tx_coalesce_usecs = 0;
	else {
		u32 clks = sky2_read32(hw, STAT_TX_TIMER_INI);
		ecmd->tx_coalesce_usecs = sky2_clk2us(hw, clks);
	}
	ecmd->tx_max_coalesced_frames = sky2_read16(hw, STAT_TX_IDX_TH);

	if (sky2_read8(hw, STAT_LEV_TIMER_CTRL) == TIM_STOP)
		ecmd->rx_coalesce_usecs = 0;
	else {
		u32 clks = sky2_read32(hw, STAT_LEV_TIMER_INI);
		ecmd->rx_coalesce_usecs = sky2_clk2us(hw, clks);
	}
	ecmd->rx_max_coalesced_frames = sky2_read8(hw, STAT_FIFO_WM);

	if (sky2_read8(hw, STAT_ISR_TIMER_CTRL) == TIM_STOP)
		ecmd->rx_coalesce_usecs_irq = 0;
	else {
		u32 clks = sky2_read32(hw, STAT_ISR_TIMER_INI);
		ecmd->rx_coalesce_usecs_irq = sky2_clk2us(hw, clks);
	}

	ecmd->rx_max_coalesced_frames_irq = sky2_read8(hw, STAT_FIFO_ISR_WM);

	return 0;
}