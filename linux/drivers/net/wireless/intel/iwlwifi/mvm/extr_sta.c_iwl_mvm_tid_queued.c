#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct iwl_mvm_tid_data {int /*<<< orphan*/  next_reclaimed; int /*<<< orphan*/  seq_number; } ;
struct iwl_mvm {TYPE_2__* trans; } ;
struct TYPE_4__ {TYPE_1__* trans_cfg; } ;
struct TYPE_3__ {scalar_t__ gen2; } ;

/* Variables and functions */
 int IEEE80211_SEQ_TO_SN (int /*<<< orphan*/ ) ; 
 int ieee80211_sn_sub (int,int /*<<< orphan*/ ) ; 

u16 iwl_mvm_tid_queued(struct iwl_mvm *mvm, struct iwl_mvm_tid_data *tid_data)
{
	u16 sn = IEEE80211_SEQ_TO_SN(tid_data->seq_number);

	/*
	 * In 22000 HW, the next_reclaimed index is only 8 bit, so we'll need
	 * to align the wrap around of ssn so we compare relevant values.
	 */
	if (mvm->trans->trans_cfg->gen2)
		sn &= 0xff;

	return ieee80211_sn_sub(sn, tid_data->next_reclaimed);
}