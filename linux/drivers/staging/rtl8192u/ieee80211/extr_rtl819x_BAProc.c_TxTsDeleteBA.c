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
struct ba_record {scalar_t__ valid; } ;
struct tx_ts_record {struct ba_record tx_pending_ba_record; struct ba_record tx_admitted_ba_record; } ;
struct ieee80211_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeActivateBAEntry (struct ieee80211_device*,struct ba_record*) ; 

__attribute__((used)) static u8 TxTsDeleteBA(struct ieee80211_device *ieee, struct tx_ts_record *pTxTs)
{
	struct ba_record *pAdmittedBa = &pTxTs->tx_admitted_ba_record;  //These two BA entries must exist in TS structure
	struct ba_record *pPendingBa = &pTxTs->tx_pending_ba_record;
	u8			bSendDELBA = false;

	// Delete pending BA
	if (pPendingBa->valid) {
		DeActivateBAEntry(ieee, pPendingBa);
		bSendDELBA = true;
	}

	// Delete admitted BA
	if (pAdmittedBa->valid) {
		DeActivateBAEntry(ieee, pAdmittedBa);
		bSendDELBA = true;
	}

	return bSendDELBA;
}