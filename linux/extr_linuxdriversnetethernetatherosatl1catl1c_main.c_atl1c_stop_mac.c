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
struct atl1c_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_READ_REG (struct atl1c_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  AT_WRITE_REG (struct atl1c_hw*,int /*<<< orphan*/ ,int) ; 
 int IDLE_STATUS_RXMAC_BUSY ; 
 int IDLE_STATUS_RXQ_BUSY ; 
 int IDLE_STATUS_TXMAC_BUSY ; 
 int IDLE_STATUS_TXQ_BUSY ; 
 int MAC_CTRL_RX_EN ; 
 int MAC_CTRL_TX_EN ; 
 int /*<<< orphan*/  REG_MAC_CTRL ; 
 int /*<<< orphan*/  REG_RXQ_CTRL ; 
 int /*<<< orphan*/  REG_TXQ_CTRL ; 
 int RXQ_CTRL_EN ; 
 int TXQ_CTRL_EN ; 
 scalar_t__ atl1c_wait_until_idle (struct atl1c_hw*,int) ; 

__attribute__((used)) static int atl1c_stop_mac(struct atl1c_hw *hw)
{
	u32 data;

	AT_READ_REG(hw, REG_RXQ_CTRL, &data);
	data &= ~RXQ_CTRL_EN;
	AT_WRITE_REG(hw, REG_RXQ_CTRL, data);

	AT_READ_REG(hw, REG_TXQ_CTRL, &data);
	data &= ~TXQ_CTRL_EN;
	AT_WRITE_REG(hw, REG_TXQ_CTRL, data);

	atl1c_wait_until_idle(hw, IDLE_STATUS_RXQ_BUSY | IDLE_STATUS_TXQ_BUSY);

	AT_READ_REG(hw, REG_MAC_CTRL, &data);
	data &= ~(MAC_CTRL_TX_EN | MAC_CTRL_RX_EN);
	AT_WRITE_REG(hw, REG_MAC_CTRL, data);

	return (int)atl1c_wait_until_idle(hw,
		IDLE_STATUS_TXMAC_BUSY | IDLE_STATUS_RXMAC_BUSY);
}