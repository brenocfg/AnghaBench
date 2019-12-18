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
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_BTCOEX_CTRL ; 
 int /*<<< orphan*/  AR_BTCOEX_CTRL2 ; 
 int /*<<< orphan*/  AR_BTCOEX_CTRL2_TX_CHAIN_MASK ; 
 int /*<<< orphan*/  AR_BTCOEX_CTRL_1_CHAIN_ACK ; 
 int /*<<< orphan*/  AR_BTCOEX_CTRL_1_CHAIN_BCN ; 
 int /*<<< orphan*/  AR_BTCOEX_CTRL_AR9462_MODE ; 
 int /*<<< orphan*/  AR_BTCOEX_CTRL_LNA_SHARED ; 
 int /*<<< orphan*/  AR_BTCOEX_CTRL_NUM_ANTENNAS ; 
 int /*<<< orphan*/  AR_BTCOEX_CTRL_ONE_STEP_LOOK_AHEAD_EN ; 
 int /*<<< orphan*/  AR_BTCOEX_CTRL_PA_SHARED ; 
 int /*<<< orphan*/  AR_BTCOEX_CTRL_RX_CHAIN_MASK ; 
 int /*<<< orphan*/  AR_BTCOEX_CTRL_WBTIMER_EN ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int SM (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar9003_mci_set_btcoex_ctrl_9565_1ANT(struct ath_hw *ah)
{
	u32 regval;

	regval = SM(1, AR_BTCOEX_CTRL_AR9462_MODE) |
		 SM(1, AR_BTCOEX_CTRL_WBTIMER_EN) |
		 SM(1, AR_BTCOEX_CTRL_PA_SHARED) |
		 SM(1, AR_BTCOEX_CTRL_LNA_SHARED) |
		 SM(1, AR_BTCOEX_CTRL_NUM_ANTENNAS) |
		 SM(1, AR_BTCOEX_CTRL_RX_CHAIN_MASK) |
		 SM(0, AR_BTCOEX_CTRL_1_CHAIN_ACK) |
		 SM(0, AR_BTCOEX_CTRL_1_CHAIN_BCN) |
		 SM(0, AR_BTCOEX_CTRL_ONE_STEP_LOOK_AHEAD_EN);

	REG_RMW_FIELD(ah, AR_BTCOEX_CTRL2,
		      AR_BTCOEX_CTRL2_TX_CHAIN_MASK, 0x1);
	REG_WRITE(ah, AR_BTCOEX_CTRL, regval);
}