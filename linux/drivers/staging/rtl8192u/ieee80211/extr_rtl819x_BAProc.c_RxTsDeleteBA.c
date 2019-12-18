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
struct rx_ts_record {struct ba_record rx_admitted_ba_record; } ;
struct ieee80211_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeActivateBAEntry (struct ieee80211_device*,struct ba_record*) ; 

__attribute__((used)) static u8 RxTsDeleteBA(struct ieee80211_device *ieee, struct rx_ts_record *pRxTs)
{
	struct ba_record       *pBa = &pRxTs->rx_admitted_ba_record;
	u8			bSendDELBA = false;

	if (pBa->valid) {
		DeActivateBAEntry(ieee, pBa);
		bSendDELBA = true;
	}

	return bSendDELBA;
}