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
typedef  int /*<<< orphan*/  u16 ;
struct ksz_port_info {int duplex; } ;
struct ksz_port {int dummy; } ;
struct ksz_hw {int features; int overrides; scalar_t__ io; int /*<<< orphan*/  tx_cfg; scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TX_FLOW_ENABLE ; 
 int HALF_DUPLEX_SIGNAL_BUG ; 
 scalar_t__ KS_DMA_TX_CTRL ; 
 int PAUSE_FLOW_CTRL ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void port_cfg_change(struct ksz_hw *hw, struct ksz_port *port,
	struct ksz_port_info *info, u16 link_status)
{
	if ((hw->features & HALF_DUPLEX_SIGNAL_BUG) &&
			!(hw->overrides & PAUSE_FLOW_CTRL)) {
		u32 cfg = hw->tx_cfg;

		/* Disable flow control in the half duplex mode. */
		if (1 == info->duplex)
			hw->tx_cfg &= ~DMA_TX_FLOW_ENABLE;
		if (hw->enabled && cfg != hw->tx_cfg)
			writel(hw->tx_cfg, hw->io + KS_DMA_TX_CTRL);
	}
}