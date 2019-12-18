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
struct ath_mci_profile {int voice_priority; scalar_t__ num_pan; scalar_t__ num_hid; scalar_t__ num_a2dp; scalar_t__ num_other_acl; scalar_t__ num_sco; scalar_t__ num_mgmt; } ;
struct ath_btcoex {struct ath_mci_profile mci; } ;
struct ath_softc {int /*<<< orphan*/  sc_ah; struct ath_btcoex btcoex; } ;
typedef  int /*<<< orphan*/  stomp_txprio ;

/* Variables and functions */
 size_t ATH_BTCOEX_STOMP_ALL ; 
 size_t ATH_BTCOEX_STOMP_LOW ; 
 int ATH_BTCOEX_STOMP_MAX ; 
 size_t ATH_BTCOEX_STOMP_NONE ; 
 int ATH_MCI_INQUIRY_PRIO ; 
 int /*<<< orphan*/  ath9k_hw_btcoex_set_concur_txprio (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ath_mci_update_stomp_txprio (int,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ath_mci_set_concur_txprio(struct ath_softc *sc)
{
	struct ath_btcoex *btcoex = &sc->btcoex;
	struct ath_mci_profile *mci = &btcoex->mci;
	u8 stomp_txprio[ATH_BTCOEX_STOMP_MAX];

	memset(stomp_txprio, 0, sizeof(stomp_txprio));
	if (mci->num_mgmt) {
		stomp_txprio[ATH_BTCOEX_STOMP_ALL] = ATH_MCI_INQUIRY_PRIO;
		if (!mci->num_pan && !mci->num_other_acl)
			stomp_txprio[ATH_BTCOEX_STOMP_NONE] =
				ATH_MCI_INQUIRY_PRIO;
	} else {
		u8 prof_prio[] = { 50, 90, 94, 52 };/* RFCOMM, A2DP, HID, PAN */

		stomp_txprio[ATH_BTCOEX_STOMP_LOW] =
		stomp_txprio[ATH_BTCOEX_STOMP_NONE] = 0xff;

		if (mci->num_sco)
			ath_mci_update_stomp_txprio(mci->voice_priority,
						    stomp_txprio);
		if (mci->num_other_acl)
			ath_mci_update_stomp_txprio(prof_prio[0], stomp_txprio);
		if (mci->num_a2dp)
			ath_mci_update_stomp_txprio(prof_prio[1], stomp_txprio);
		if (mci->num_hid)
			ath_mci_update_stomp_txprio(prof_prio[2], stomp_txprio);
		if (mci->num_pan)
			ath_mci_update_stomp_txprio(prof_prio[3], stomp_txprio);

		if (stomp_txprio[ATH_BTCOEX_STOMP_NONE] == 0xff)
			stomp_txprio[ATH_BTCOEX_STOMP_NONE] = 0;

		if (stomp_txprio[ATH_BTCOEX_STOMP_LOW] == 0xff)
			stomp_txprio[ATH_BTCOEX_STOMP_LOW] = 0;
	}
	ath9k_hw_btcoex_set_concur_txprio(sc->sc_ah, stomp_txprio);
}