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
typedef  int u32 ;
struct ath9k_hw_mci {scalar_t__ bt_state; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {scalar_t__ power_mode; TYPE_1__ btcoex_hw; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 scalar_t__ AR_BTCOEX_CTRL ; 
 int AR_BTCOEX_CTRL_MCI_MODE_EN ; 
 scalar_t__ AR_MCI_COMMAND0 ; 
 int /*<<< orphan*/  AR_MCI_COMMAND0_DISABLE_TIMESTAMP ; 
 int /*<<< orphan*/  AR_MCI_COMMAND0_HEADER ; 
 int /*<<< orphan*/  AR_MCI_COMMAND0_LEN ; 
 scalar_t__ AR_MCI_INTERRUPT_EN ; 
 int AR_MCI_INTERRUPT_MSG_FAIL_MASK ; 
 scalar_t__ AR_MCI_INTERRUPT_RAW ; 
 int AR_MCI_INTERRUPT_SW_MSG_DONE ; 
 scalar_t__ AR_MCI_TX_PAYLOAD0 ; 
 scalar_t__ ATH9K_PM_FULL_SLEEP ; 
 int /*<<< orphan*/  MCI ; 
 scalar_t__ MCI_BT_SLEEP ; 
 int MCI_FLAG_DISABLE_TIMESTAMP ; 
 int REG_READ (struct ath_hw*,scalar_t__) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,scalar_t__,int) ; 
 int SM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9003_mci_queue_unsent_gpm (struct ath_hw*,int,int*,int) ; 
 int /*<<< orphan*/  ar9003_mci_wait_for_interrupt (struct ath_hw*,scalar_t__,int,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int,...) ; 

bool ar9003_mci_send_message(struct ath_hw *ah, u8 header, u32 flag,
			     u32 *payload, u8 len, bool wait_done,
			     bool check_bt)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	bool msg_sent = false;
	u32 regval;
	u32 saved_mci_int_en;
	int i;

	saved_mci_int_en = REG_READ(ah, AR_MCI_INTERRUPT_EN);
	regval = REG_READ(ah, AR_BTCOEX_CTRL);

	if ((regval == 0xdeadbeef) || !(regval & AR_BTCOEX_CTRL_MCI_MODE_EN)) {
		ath_dbg(common, MCI,
			"MCI Not sending 0x%x. MCI is not enabled. full_sleep = %d\n",
			header, (ah->power_mode == ATH9K_PM_FULL_SLEEP) ? 1 : 0);
		ar9003_mci_queue_unsent_gpm(ah, header, payload, true);
		return false;
	} else if (check_bt && (mci->bt_state == MCI_BT_SLEEP)) {
		ath_dbg(common, MCI,
			"MCI Don't send message 0x%x. BT is in sleep state\n",
			header);
		ar9003_mci_queue_unsent_gpm(ah, header, payload, true);
		return false;
	}

	if (wait_done)
		REG_WRITE(ah, AR_MCI_INTERRUPT_EN, 0);

	/* Need to clear SW_MSG_DONE raw bit before wait */

	REG_WRITE(ah, AR_MCI_INTERRUPT_RAW,
		  (AR_MCI_INTERRUPT_SW_MSG_DONE |
		   AR_MCI_INTERRUPT_MSG_FAIL_MASK));

	if (payload) {
		for (i = 0; (i * 4) < len; i++)
			REG_WRITE(ah, (AR_MCI_TX_PAYLOAD0 + i * 4),
				  *(payload + i));
	}

	REG_WRITE(ah, AR_MCI_COMMAND0,
		  (SM((flag & MCI_FLAG_DISABLE_TIMESTAMP),
		      AR_MCI_COMMAND0_DISABLE_TIMESTAMP) |
		   SM(len, AR_MCI_COMMAND0_LEN) |
		   SM(header, AR_MCI_COMMAND0_HEADER)));

	if (wait_done &&
	    !(ar9003_mci_wait_for_interrupt(ah, AR_MCI_INTERRUPT_RAW,
					    AR_MCI_INTERRUPT_SW_MSG_DONE, 500)))
		ar9003_mci_queue_unsent_gpm(ah, header, payload, true);
	else {
		ar9003_mci_queue_unsent_gpm(ah, header, payload, false);
		msg_sent = true;
	}

	if (wait_done)
		REG_WRITE(ah, AR_MCI_INTERRUPT_EN, saved_mci_int_en);

	return msg_sent;
}