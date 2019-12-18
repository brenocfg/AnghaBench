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
struct ath9k_hw_mci {int is_2g; int update_2g5g; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_BTCOEX_CTRL_BT_OWN_SPDT_CTRL ; 
 int /*<<< orphan*/  AR_PHY_GLB_CONTROL ; 
 int /*<<< orphan*/  MCI ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9003_mci_send_2g5g_status (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_mci_send_lna_take (struct ath_hw*,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

void ar9003_mci_bt_gain_ctrl(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	ath_dbg(common, MCI, "Give LNA and SPDT control to BT\n");

	ar9003_mci_send_lna_take(ah, true);
	udelay(50);

	REG_SET_BIT(ah, AR_PHY_GLB_CONTROL, AR_BTCOEX_CTRL_BT_OWN_SPDT_CTRL);
	mci->is_2g = false;
	mci->update_2g5g = true;
	ar9003_mci_send_2g5g_status(ah, true);

	/* Force another 2g5g update at next scanning */
	mci->update_2g5g = true;
}