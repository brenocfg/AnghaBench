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
struct mwifiex_private {int /*<<< orphan*/  bss_mode; struct mwifiex_adapter* adapter; } ;
struct TYPE_5__ {int status; } ;
struct mwifiex_adapter {int /*<<< orphan*/  mwifiex_cmd_lock; TYPE_4__* curr_cmd; int /*<<< orphan*/  ps_mode; TYPE_1__ cmd_wait_q; } ;
struct TYPE_7__ {int /*<<< orphan*/  ps_bitmap; } ;
struct host_cmd_ds_802_11_ps_mode_enh {TYPE_3__ params; int /*<<< orphan*/  action; } ;
struct TYPE_6__ {struct host_cmd_ds_802_11_ps_mode_enh psmode_enh; } ;
struct host_cmd_ds_command {int /*<<< orphan*/  result; TYPE_2__ params; int /*<<< orphan*/  command; } ;
struct TYPE_8__ {scalar_t__ wait_q_enabled; } ;

/* Variables and functions */
 int BITMAP_STA_PS ; 
 int EN_AUTO_PS ; 
 int /*<<< orphan*/  ERROR ; 
#define  HostCmd_CMD_802_11_PS_MODE_ENH 132 
#define  HostCmd_CMD_802_11_SCAN 131 
#define  HostCmd_CMD_802_11_SCAN_EXT 130 
#define  HostCmd_CMD_MAC_CONTROL 129 
#define  HostCmd_CMD_SDIO_SP_RX_AGGR_CFG 128 
 int /*<<< orphan*/  MSG ; 
 int /*<<< orphan*/  MWIFIEX_802_11_POWER_MODE_CAM ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_cancel_scan (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mwifiex_recycle_cmd_node (struct mwifiex_adapter*,TYPE_4__*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mwifiex_process_cmdresp_error(struct mwifiex_private *priv,
			      struct host_cmd_ds_command *resp)
{
	struct mwifiex_adapter *adapter = priv->adapter;
	struct host_cmd_ds_802_11_ps_mode_enh *pm;

	mwifiex_dbg(adapter, ERROR,
		    "CMD_RESP: cmd %#x error, result=%#x\n",
		    resp->command, resp->result);

	if (adapter->curr_cmd->wait_q_enabled)
		adapter->cmd_wait_q.status = -1;

	switch (le16_to_cpu(resp->command)) {
	case HostCmd_CMD_802_11_PS_MODE_ENH:
		pm = &resp->params.psmode_enh;
		mwifiex_dbg(adapter, ERROR,
			    "PS_MODE_ENH cmd failed: result=0x%x action=0x%X\n",
			    resp->result, le16_to_cpu(pm->action));
		/* We do not re-try enter-ps command in ad-hoc mode. */
		if (le16_to_cpu(pm->action) == EN_AUTO_PS &&
		    (le16_to_cpu(pm->params.ps_bitmap) & BITMAP_STA_PS) &&
		    priv->bss_mode == NL80211_IFTYPE_ADHOC)
			adapter->ps_mode = MWIFIEX_802_11_POWER_MODE_CAM;

		break;
	case HostCmd_CMD_802_11_SCAN:
	case HostCmd_CMD_802_11_SCAN_EXT:
		mwifiex_cancel_scan(adapter);
		break;

	case HostCmd_CMD_MAC_CONTROL:
		break;

	case HostCmd_CMD_SDIO_SP_RX_AGGR_CFG:
		mwifiex_dbg(adapter, MSG,
			    "SDIO RX single-port aggregation Not support\n");
		break;

	default:
		break;
	}
	/* Handling errors here */
	mwifiex_recycle_cmd_node(adapter, adapter->curr_cmd);

	spin_lock_bh(&adapter->mwifiex_cmd_lock);
	adapter->curr_cmd = NULL;
	spin_unlock_bh(&adapter->mwifiex_cmd_lock);
}