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
struct ba_record {scalar_t__ bValid; } ;
struct tx_ts_record {struct ba_record TxPendingBARecord; struct ba_record TxAdmittedBARecord; } ;
struct rtllib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeActivateBAEntry (struct rtllib_device*,struct ba_record*) ; 

__attribute__((used)) static u8 TxTsDeleteBA(struct rtllib_device *ieee, struct tx_ts_record *pTxTs)
{
	struct ba_record *pAdmittedBa = &pTxTs->TxAdmittedBARecord;
	struct ba_record *pPendingBa = &pTxTs->TxPendingBARecord;
	u8 bSendDELBA = false;

	if (pPendingBa->bValid) {
		DeActivateBAEntry(ieee, pPendingBa);
		bSendDELBA = true;
	}

	if (pAdmittedBa->bValid) {
		DeActivateBAEntry(ieee, pAdmittedBa);
		bSendDELBA = true;
	}
	return bSendDELBA;
}