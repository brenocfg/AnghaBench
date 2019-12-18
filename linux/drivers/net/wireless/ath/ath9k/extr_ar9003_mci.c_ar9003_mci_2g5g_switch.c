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
struct ath9k_hw_mci {int config; scalar_t__ is_2g; int /*<<< orphan*/  update_2g5g; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_BTCOEX_CTRL_BT_OWN_SPDT_CTRL ; 
 int /*<<< orphan*/  AR_MCI_TX_CTRL ; 
 int /*<<< orphan*/  AR_MCI_TX_CTRL_DISABLE_LNA_UPDATE ; 
 int /*<<< orphan*/  AR_PHY_GLB_CONTROL ; 
 int /*<<< orphan*/  AR_SELFGEN_MASK ; 
 scalar_t__ AR_SREV_9462 (struct ath_hw*) ; 
 int ATH_MCI_CONFIG_DISABLE_OSLA ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar9003_mci_osla_setup (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_mci_send_2g5g_status (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_mci_send_lna_take (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_mci_send_lna_transfer (struct ath_hw*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void ar9003_mci_2g5g_switch(struct ath_hw *ah, bool force)
{
	struct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	if (!mci->update_2g5g && !force)
		return;

	if (mci->is_2g) {
		ar9003_mci_send_2g5g_status(ah, true);
		ar9003_mci_send_lna_transfer(ah, true);
		udelay(5);

		REG_CLR_BIT(ah, AR_MCI_TX_CTRL,
			    AR_MCI_TX_CTRL_DISABLE_LNA_UPDATE);
		REG_CLR_BIT(ah, AR_PHY_GLB_CONTROL,
			    AR_BTCOEX_CTRL_BT_OWN_SPDT_CTRL);

		if (!(mci->config & ATH_MCI_CONFIG_DISABLE_OSLA))
			ar9003_mci_osla_setup(ah, true);

		if (AR_SREV_9462(ah))
			REG_WRITE(ah, AR_SELFGEN_MASK, 0x02);
	} else {
		ar9003_mci_send_lna_take(ah, true);
		udelay(5);

		REG_SET_BIT(ah, AR_MCI_TX_CTRL,
			    AR_MCI_TX_CTRL_DISABLE_LNA_UPDATE);
		REG_SET_BIT(ah, AR_PHY_GLB_CONTROL,
			    AR_BTCOEX_CTRL_BT_OWN_SPDT_CTRL);

		ar9003_mci_osla_setup(ah, false);
		ar9003_mci_send_2g5g_status(ah, true);
	}
}