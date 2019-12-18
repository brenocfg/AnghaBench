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
typedef  int u8 ;
struct TYPE_2__ {int tx_chainmask; int rx_chainmask; int hw_caps; } ;
struct ath_hw {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_ANALOG_SWAP ; 
 int /*<<< orphan*/  AR_PHY_CAL_CHAINMASK ; 
 int /*<<< orphan*/  AR_PHY_RX_CHAINMASK ; 
 int /*<<< orphan*/  AR_PHY_SWAP_ALT_CHAIN ; 
 int /*<<< orphan*/  AR_SELFGEN_MASK ; 
 int ATH9K_HW_CAP_APM ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 

void ar9003_hw_set_chain_masks(struct ath_hw *ah, u8 rx, u8 tx)
{
	if (ah->caps.tx_chainmask == 5 || ah->caps.rx_chainmask == 5)
		REG_SET_BIT(ah, AR_PHY_ANALOG_SWAP,
			    AR_PHY_SWAP_ALT_CHAIN);

	REG_WRITE(ah, AR_PHY_RX_CHAINMASK, rx);
	REG_WRITE(ah, AR_PHY_CAL_CHAINMASK, rx);

	if ((ah->caps.hw_caps & ATH9K_HW_CAP_APM) && (tx == 0x7))
		tx = 3;

	REG_WRITE(ah, AR_SELFGEN_MASK, tx);
}