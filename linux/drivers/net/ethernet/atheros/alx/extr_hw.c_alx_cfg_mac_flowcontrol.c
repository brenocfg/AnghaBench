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
typedef  int u8 ;
struct alx_hw {int /*<<< orphan*/  rx_ctrl; } ;

/* Variables and functions */
 int ALX_FC_RX ; 
 int ALX_FC_TX ; 
 int /*<<< orphan*/  ALX_MAC_CTRL ; 
 int /*<<< orphan*/  ALX_MAC_CTRL_RXFC_EN ; 
 int /*<<< orphan*/  ALX_MAC_CTRL_TXFC_EN ; 
 int /*<<< orphan*/  alx_write_mem32 (struct alx_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void alx_cfg_mac_flowcontrol(struct alx_hw *hw, u8 fc)
{
	if (fc & ALX_FC_RX)
		hw->rx_ctrl |= ALX_MAC_CTRL_RXFC_EN;
	else
		hw->rx_ctrl &= ~ALX_MAC_CTRL_RXFC_EN;

	if (fc & ALX_FC_TX)
		hw->rx_ctrl |= ALX_MAC_CTRL_TXFC_EN;
	else
		hw->rx_ctrl &= ~ALX_MAC_CTRL_TXFC_EN;

	alx_write_mem32(hw, ALX_MAC_CTRL, hw->rx_ctrl);
}