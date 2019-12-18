#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  size_t u8 ;
typedef  int u32 ;
struct mwifiex_sta_node {scalar_t__ is_11ac_enabled; } ;
struct TYPE_6__ {int rx_win_size; int /*<<< orphan*/  rx_amsdu; } ;
struct mwifiex_private {TYPE_3__* aggr_prio_tbl; TYPE_2__ add_ba_param; int /*<<< orphan*/  sta_list_spinlock; TYPE_4__* adapter; int /*<<< orphan*/  cfg_bssid; } ;
struct host_cmd_ds_11n_addba_rsp {void* block_ack_param_set; void* status_code; void* ssn; int /*<<< orphan*/  block_ack_tmo; int /*<<< orphan*/  dialog_token; int /*<<< orphan*/  peer_mac_addr; } ;
struct TYPE_5__ {struct host_cmd_ds_11n_addba_rsp add_ba_rsp; } ;
struct host_cmd_ds_command {void* size; void* command; TYPE_1__ params; } ;
struct host_cmd_ds_11n_addba_req {void* ssn; int /*<<< orphan*/  peer_mac_addr; void* block_ack_param_set; int /*<<< orphan*/  block_ack_tmo; int /*<<< orphan*/  dialog_token; } ;
struct TYPE_8__ {scalar_t__ is_hw_11ac_capable; int /*<<< orphan*/  fw_cap_info; } ;
struct TYPE_7__ {scalar_t__ amsdu; } ;

/* Variables and functions */
 int ADDBA_RSP_STATUS_ACCEPT ; 
 scalar_t__ BA_STREAM_NOT_ALLOWED ; 
 int BLOCKACKPARAM_AMSDU_SUPP_MASK ; 
 int BLOCKACKPARAM_TID_POS ; 
 int BLOCKACKPARAM_WINSIZE_POS ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ GET_BSS_ROLE (struct mwifiex_private*) ; 
 int HostCmd_CMD_11N_ADDBA_RSP ; 
 int IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK ; 
 int IEEE80211_ADDBA_PARAM_TID_MASK ; 
 scalar_t__ ISSUPP_TDLS_ENABLED (int /*<<< orphan*/ ) ; 
 int MWIFIEX_11AC_STA_AMPDU_DEF_RXWINSIZE ; 
 scalar_t__ MWIFIEX_BSS_ROLE_STA ; 
 int S_DS_GEN ; 
 void* cpu_to_le16 (int) ; 
 int le16_to_cpu (void*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_11n_create_rx_reorder_tbl (struct mwifiex_private*,int /*<<< orphan*/ ,size_t,int,int) ; 
 int /*<<< orphan*/  mwifiex_dbg (TYPE_4__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct mwifiex_sta_node* mwifiex_get_sta_entry (struct mwifiex_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int mwifiex_cmd_11n_addba_rsp_gen(struct mwifiex_private *priv,
				  struct host_cmd_ds_command *cmd,
				  struct host_cmd_ds_11n_addba_req
				  *cmd_addba_req)
{
	struct host_cmd_ds_11n_addba_rsp *add_ba_rsp = &cmd->params.add_ba_rsp;
	struct mwifiex_sta_node *sta_ptr;
	u32 rx_win_size = priv->add_ba_param.rx_win_size;
	u8 tid;
	int win_size;
	uint16_t block_ack_param_set;

	if ((GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA) &&
	    ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info) &&
	    priv->adapter->is_hw_11ac_capable &&
	    memcmp(priv->cfg_bssid, cmd_addba_req->peer_mac_addr, ETH_ALEN)) {
		spin_lock_bh(&priv->sta_list_spinlock);
		sta_ptr = mwifiex_get_sta_entry(priv,
						cmd_addba_req->peer_mac_addr);
		if (!sta_ptr) {
			spin_unlock_bh(&priv->sta_list_spinlock);
			mwifiex_dbg(priv->adapter, ERROR,
				    "BA setup with unknown TDLS peer %pM!\n",
				    cmd_addba_req->peer_mac_addr);
			return -1;
		}
		if (sta_ptr->is_11ac_enabled)
			rx_win_size = MWIFIEX_11AC_STA_AMPDU_DEF_RXWINSIZE;
		spin_unlock_bh(&priv->sta_list_spinlock);
	}

	cmd->command = cpu_to_le16(HostCmd_CMD_11N_ADDBA_RSP);
	cmd->size = cpu_to_le16(sizeof(*add_ba_rsp) + S_DS_GEN);

	memcpy(add_ba_rsp->peer_mac_addr, cmd_addba_req->peer_mac_addr,
	       ETH_ALEN);
	add_ba_rsp->dialog_token = cmd_addba_req->dialog_token;
	add_ba_rsp->block_ack_tmo = cmd_addba_req->block_ack_tmo;
	add_ba_rsp->ssn = cmd_addba_req->ssn;

	block_ack_param_set = le16_to_cpu(cmd_addba_req->block_ack_param_set);
	tid = (block_ack_param_set & IEEE80211_ADDBA_PARAM_TID_MASK)
		>> BLOCKACKPARAM_TID_POS;
	add_ba_rsp->status_code = cpu_to_le16(ADDBA_RSP_STATUS_ACCEPT);
	block_ack_param_set &= ~IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK;

	/* If we don't support AMSDU inside AMPDU, reset the bit */
	if (!priv->add_ba_param.rx_amsdu ||
	    (priv->aggr_prio_tbl[tid].amsdu == BA_STREAM_NOT_ALLOWED))
		block_ack_param_set &= ~BLOCKACKPARAM_AMSDU_SUPP_MASK;
	block_ack_param_set |= rx_win_size << BLOCKACKPARAM_WINSIZE_POS;
	add_ba_rsp->block_ack_param_set = cpu_to_le16(block_ack_param_set);
	win_size = (le16_to_cpu(add_ba_rsp->block_ack_param_set)
					& IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK)
					>> BLOCKACKPARAM_WINSIZE_POS;
	cmd_addba_req->block_ack_param_set = cpu_to_le16(block_ack_param_set);

	mwifiex_11n_create_rx_reorder_tbl(priv, cmd_addba_req->peer_mac_addr,
					  tid, win_size,
					  le16_to_cpu(cmd_addba_req->ssn));
	return 0;
}