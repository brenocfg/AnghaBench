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
typedef  size_t u8 ;
typedef  void iwl_mvm_txq ;
struct ieee80211_sta {TYPE_1__** txq; } ;
struct TYPE_2__ {scalar_t__ drv_priv; } ;

/* Variables and functions */
 size_t IEEE80211_NUM_TIDS ; 
 size_t IWL_MAX_TID_COUNT ; 

__attribute__((used)) static inline struct iwl_mvm_txq *
iwl_mvm_txq_from_tid(struct ieee80211_sta *sta, u8 tid)
{
	if (tid == IWL_MAX_TID_COUNT)
		tid = IEEE80211_NUM_TIDS;

	return (void *)sta->txq[tid]->drv_priv;
}