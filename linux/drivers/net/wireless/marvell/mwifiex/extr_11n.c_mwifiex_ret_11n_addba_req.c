#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct mwifiex_tx_ba_stream_tbl {int amsdu; void* ba_status; } ;
struct mwifiex_ra_list_tbl {int amsdu_in_ampdu; void* ba_status; } ;
struct TYPE_5__ {scalar_t__ tx_amsdu; } ;
struct mwifiex_private {int /*<<< orphan*/  adapter; TYPE_3__* aggr_prio_tbl; TYPE_2__ add_ba_param; } ;
struct host_cmd_ds_11n_addba_rsp {scalar_t__ add_rsp_result; int /*<<< orphan*/  peer_mac_addr; int /*<<< orphan*/  status_code; int /*<<< orphan*/  ssn; int /*<<< orphan*/  block_ack_param_set; } ;
struct TYPE_4__ {struct host_cmd_ds_11n_addba_rsp add_ba_rsp; } ;
struct host_cmd_ds_command {TYPE_1__ params; } ;
struct TYPE_6__ {scalar_t__ amsdu; scalar_t__ ampdu_ap; } ;

/* Variables and functions */
 int BA_RESULT_SUCCESS ; 
 scalar_t__ BA_RESULT_TIMEOUT ; 
 void* BA_SETUP_COMPLETE ; 
 void* BA_SETUP_NONE ; 
 scalar_t__ BA_STREAM_NOT_ALLOWED ; 
 int BLOCKACKPARAM_AMSDU_SUPP_MASK ; 
 int BLOCKACKPARAM_TID_POS ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EVENT ; 
 int IEEE80211_ADDBA_PARAM_TID_MASK ; 
 int SSN_MASK ; 
 int /*<<< orphan*/  TYPE_DELBA_SENT ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mwifiex_del_ba_tbl (struct mwifiex_private*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mwifiex_tx_ba_stream_tbl* mwifiex_get_ba_tbl (struct mwifiex_private*,int,int /*<<< orphan*/ ) ; 
 int mwifiex_wmm_downgrade_tid (struct mwifiex_private*,int) ; 
 struct mwifiex_ra_list_tbl* mwifiex_wmm_get_ralist_node (struct mwifiex_private*,int,int /*<<< orphan*/ ) ; 

int mwifiex_ret_11n_addba_req(struct mwifiex_private *priv,
			      struct host_cmd_ds_command *resp)
{
	int tid, tid_down;
	struct host_cmd_ds_11n_addba_rsp *add_ba_rsp = &resp->params.add_ba_rsp;
	struct mwifiex_tx_ba_stream_tbl *tx_ba_tbl;
	struct mwifiex_ra_list_tbl *ra_list;
	u16 block_ack_param_set = le16_to_cpu(add_ba_rsp->block_ack_param_set);

	add_ba_rsp->ssn = cpu_to_le16((le16_to_cpu(add_ba_rsp->ssn))
			& SSN_MASK);

	tid = (block_ack_param_set & IEEE80211_ADDBA_PARAM_TID_MASK)
	       >> BLOCKACKPARAM_TID_POS;

	tid_down = mwifiex_wmm_downgrade_tid(priv, tid);
	ra_list = mwifiex_wmm_get_ralist_node(priv, tid_down, add_ba_rsp->
		peer_mac_addr);
	if (le16_to_cpu(add_ba_rsp->status_code) != BA_RESULT_SUCCESS) {
		if (ra_list) {
			ra_list->ba_status = BA_SETUP_NONE;
			ra_list->amsdu_in_ampdu = false;
		}
		mwifiex_del_ba_tbl(priv, tid, add_ba_rsp->peer_mac_addr,
				   TYPE_DELBA_SENT, true);
		if (add_ba_rsp->add_rsp_result != BA_RESULT_TIMEOUT)
			priv->aggr_prio_tbl[tid].ampdu_ap =
				BA_STREAM_NOT_ALLOWED;
		return 0;
	}

	tx_ba_tbl = mwifiex_get_ba_tbl(priv, tid, add_ba_rsp->peer_mac_addr);
	if (tx_ba_tbl) {
		mwifiex_dbg(priv->adapter, EVENT, "info: BA stream complete\n");
		tx_ba_tbl->ba_status = BA_SETUP_COMPLETE;
		if ((block_ack_param_set & BLOCKACKPARAM_AMSDU_SUPP_MASK) &&
		    priv->add_ba_param.tx_amsdu &&
		    (priv->aggr_prio_tbl[tid].amsdu != BA_STREAM_NOT_ALLOWED))
			tx_ba_tbl->amsdu = true;
		else
			tx_ba_tbl->amsdu = false;
		if (ra_list) {
			ra_list->amsdu_in_ampdu = tx_ba_tbl->amsdu;
			ra_list->ba_status = BA_SETUP_COMPLETE;
		}
	} else {
		mwifiex_dbg(priv->adapter, ERROR, "BA stream not created\n");
	}

	return 0;
}