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
struct ksz_hw {int features; int dev_count; int /*<<< orphan*/  rx_cfg; scalar_t__ io; scalar_t__ ksz_switch; } ;
struct dev_info {int /*<<< orphan*/  dev_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RX_ERROR ; 
 scalar_t__ KS8842_SWITCH_CTRL_2_OFFSET ; 
 int RX_HUGE_FRAME ; 
 int /*<<< orphan*/  SWITCH_HUGE_PACKET ; 
 int /*<<< orphan*/  dev_rcv_packets ; 
 int /*<<< orphan*/  dev_rcv_special ; 
 int /*<<< orphan*/  port_rcv_packets ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hw_cfg_huge_frame(struct dev_info *hw_priv, struct ksz_hw *hw)
{
	if (hw->ksz_switch) {
		u32 data;

		data = readw(hw->io + KS8842_SWITCH_CTRL_2_OFFSET);
		if (hw->features & RX_HUGE_FRAME)
			data |= SWITCH_HUGE_PACKET;
		else
			data &= ~SWITCH_HUGE_PACKET;
		writew(data, hw->io + KS8842_SWITCH_CTRL_2_OFFSET);
	}
	if (hw->features & RX_HUGE_FRAME) {
		hw->rx_cfg |= DMA_RX_ERROR;
		hw_priv->dev_rcv = dev_rcv_special;
	} else {
		hw->rx_cfg &= ~DMA_RX_ERROR;
		if (hw->dev_count > 1)
			hw_priv->dev_rcv = port_rcv_packets;
		else
			hw_priv->dev_rcv = dev_rcv_packets;
	}
}