#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_8__ {int /*<<< orphan*/  uc_tsid; } ;
struct TYPE_9__ {TYPE_1__ ts_info; } ;
struct TYPE_14__ {int /*<<< orphan*/  addr; TYPE_2__ t_spec; } ;
struct TYPE_12__ {int seq_num; } ;
struct TYPE_13__ {TYPE_5__ field; } ;
struct TYPE_10__ {int buffer_size; int /*<<< orphan*/  tid; int /*<<< orphan*/  ba_policy; scalar_t__ amsdu_support; } ;
struct TYPE_11__ {TYPE_3__ field; } ;
struct ba_record {TYPE_6__ start_seq_ctrl; scalar_t__ timeout_value; TYPE_4__ param_set; int /*<<< orphan*/  dialog_token; scalar_t__ valid; } ;
struct tx_ts_record {int tx_cur_seq; TYPE_7__ ts_common_info; struct ba_record tx_pending_ba_record; } ;
struct ieee80211_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ActivateBAEntry (struct ieee80211_device*,struct ba_record*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BA_SETUP_TIMEOUT ; 
 int /*<<< orphan*/  DeActivateBAEntry (struct ieee80211_device*,struct ba_record*) ; 
 int /*<<< orphan*/  ieee80211_send_ADDBAReq (struct ieee80211_device*,int /*<<< orphan*/ ,struct ba_record*) ; 

void
TsInitAddBA(
	struct ieee80211_device *ieee,
	struct tx_ts_record     *pTS,
	u8		Policy,
	u8		bOverwritePending
	)
{
	struct ba_record *pBA = &pTS->tx_pending_ba_record;

	if (pBA->valid && !bOverwritePending)
		return;

	// Set parameters to "Pending" variable set
	DeActivateBAEntry(ieee, pBA);

	pBA->dialog_token++;						// DialogToken: Only keep the latest dialog token
	pBA->param_set.field.amsdu_support = 0;	// Do not support A-MSDU with A-MPDU now!!
	pBA->param_set.field.ba_policy = Policy;	// Policy: Delayed or Immediate
	pBA->param_set.field.tid = pTS->ts_common_info.t_spec.ts_info.uc_tsid;	// TID
	// buffer_size: This need to be set according to A-MPDU vector
	pBA->param_set.field.buffer_size = 32;		// buffer_size: This need to be set according to A-MPDU vector
	pBA->timeout_value = 0;					// Timeout value: Set 0 to disable Timer
	pBA->start_seq_ctrl.field.seq_num = (pTS->tx_cur_seq + 3) % 4096;	// Block Ack will start after 3 packets later.

	ActivateBAEntry(ieee, pBA, BA_SETUP_TIMEOUT);

	ieee80211_send_ADDBAReq(ieee, pTS->ts_common_info.addr, pBA);
}