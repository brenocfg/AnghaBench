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
struct atl1c_hw {int mac_duplex; int /*<<< orphan*/  preamble_len; int /*<<< orphan*/  mac_speed; } ;
struct atl1c_adapter {scalar_t__ link_duplex; scalar_t__ link_speed; struct atl1c_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_READ_REG (struct atl1c_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  AT_WRITE_REG (struct atl1c_hw*,int /*<<< orphan*/ ,int) ; 
 int FIELD_SETX (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FULL_DUPLEX ; 
 int MAC_CTRL_ADD_CRC ; 
 int MAC_CTRL_BC_EN ; 
 int MAC_CTRL_DUPLX ; 
 int MAC_CTRL_HASH_ALG_CRC32 ; 
 int MAC_CTRL_PAD ; 
 int /*<<< orphan*/  MAC_CTRL_PRMLEN ; 
 int MAC_CTRL_RX_EN ; 
 int MAC_CTRL_RX_FLOW ; 
 int MAC_CTRL_SINGLE_PAUSE_EN ; 
 int /*<<< orphan*/  MAC_CTRL_SPEED ; 
 int MAC_CTRL_TX_EN ; 
 int MAC_CTRL_TX_FLOW ; 
 int /*<<< orphan*/  REG_MAC_CTRL ; 
 int /*<<< orphan*/  REG_RXQ_CTRL ; 
 int /*<<< orphan*/  REG_TXQ_CTRL ; 
 int RXQ_CTRL_EN ; 
 scalar_t__ SPEED_1000 ; 
 int TXQ_CTRL_EN ; 
 int /*<<< orphan*/  atl1c_mac_speed_1000 ; 
 int /*<<< orphan*/  atl1c_mac_speed_10_100 ; 

__attribute__((used)) static void atl1c_start_mac(struct atl1c_adapter *adapter)
{
	struct atl1c_hw *hw = &adapter->hw;
	u32 mac, txq, rxq;

	hw->mac_duplex = adapter->link_duplex == FULL_DUPLEX ? true : false;
	hw->mac_speed = adapter->link_speed == SPEED_1000 ?
		atl1c_mac_speed_1000 : atl1c_mac_speed_10_100;

	AT_READ_REG(hw, REG_TXQ_CTRL, &txq);
	AT_READ_REG(hw, REG_RXQ_CTRL, &rxq);
	AT_READ_REG(hw, REG_MAC_CTRL, &mac);

	txq |= TXQ_CTRL_EN;
	rxq |= RXQ_CTRL_EN;
	mac |= MAC_CTRL_TX_EN | MAC_CTRL_TX_FLOW |
	       MAC_CTRL_RX_EN | MAC_CTRL_RX_FLOW |
	       MAC_CTRL_ADD_CRC | MAC_CTRL_PAD |
	       MAC_CTRL_BC_EN | MAC_CTRL_SINGLE_PAUSE_EN |
	       MAC_CTRL_HASH_ALG_CRC32;
	if (hw->mac_duplex)
		mac |= MAC_CTRL_DUPLX;
	else
		mac &= ~MAC_CTRL_DUPLX;
	mac = FIELD_SETX(mac, MAC_CTRL_SPEED, hw->mac_speed);
	mac = FIELD_SETX(mac, MAC_CTRL_PRMLEN, hw->preamble_len);

	AT_WRITE_REG(hw, REG_TXQ_CTRL, txq);
	AT_WRITE_REG(hw, REG_RXQ_CTRL, rxq);
	AT_WRITE_REG(hw, REG_MAC_CTRL, mac);
}