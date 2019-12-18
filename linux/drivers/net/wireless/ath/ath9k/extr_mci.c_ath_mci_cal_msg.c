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
typedef  int /*<<< orphan*/  u32 ;
struct ath_softc {struct ath_hw* sc_ah; } ;
struct ath9k_hw_mci {int /*<<< orphan*/  bt_state; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCI ; 
 int /*<<< orphan*/  MCI_BT_AWAKE ; 
 int /*<<< orphan*/  MCI_BT_CAL_START ; 
 int /*<<< orphan*/  MCI_GPM ; 
#define  MCI_GPM_BT_CAL_GRANT 129 
#define  MCI_GPM_BT_CAL_REQ 128 
 int /*<<< orphan*/  MCI_GPM_SET_CAL_TYPE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCI_GPM_WLAN_CAL_DONE ; 
 int /*<<< orphan*/  RESET_TYPE_MCI ; 
 int /*<<< orphan*/  ar9003_mci_send_message (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_queue_reset (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void ath_mci_cal_msg(struct ath_softc *sc, u8 opcode, u8 *rx_payload)
{
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;
	u32 payload[4] = {0, 0, 0, 0};

	switch (opcode) {
	case MCI_GPM_BT_CAL_REQ:
		if (mci_hw->bt_state == MCI_BT_AWAKE) {
			mci_hw->bt_state = MCI_BT_CAL_START;
			ath9k_queue_reset(sc, RESET_TYPE_MCI);
		}
		ath_dbg(common, MCI, "MCI State : %d\n", mci_hw->bt_state);
		break;
	case MCI_GPM_BT_CAL_GRANT:
		MCI_GPM_SET_CAL_TYPE(payload, MCI_GPM_WLAN_CAL_DONE);
		ar9003_mci_send_message(sc->sc_ah, MCI_GPM, 0, payload,
					16, false, true);
		break;
	default:
		ath_dbg(common, MCI, "Unknown GPM CAL message\n");
		break;
	}
}