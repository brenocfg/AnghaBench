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
typedef  int /*<<< orphan*/  u8 ;
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rem_sta_resp {int status; } ;
struct iwl_rem_sta_cmd {int num_sta; int /*<<< orphan*/  addr; } ;
struct iwl_priv {int /*<<< orphan*/  sta_lock; } ;
struct iwl_host_cmd {struct iwl_rx_packet* resp_pkt; int /*<<< orphan*/  flags; int /*<<< orphan*/  data; int /*<<< orphan*/  len; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  rm_sta_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_WANT_SKB ; 
 int EIO ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IWL_DEBUG_ASSOC (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*) ; 
#define  REM_STA_SUCCESS_MSK 128 
 int /*<<< orphan*/  REPLY_REMOVE_STA ; 
 int iwl_dvm_send_cmd (struct iwl_priv*,struct iwl_host_cmd*) ; 
 int /*<<< orphan*/  iwl_free_resp (struct iwl_host_cmd*) ; 
 int /*<<< orphan*/  iwl_sta_ucode_deactivate (struct iwl_priv*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct iwl_rem_sta_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_send_remove_station(struct iwl_priv *priv,
				   const u8 *addr, int sta_id,
				   bool temporary)
{
	struct iwl_rx_packet *pkt;
	int ret;
	struct iwl_rem_sta_cmd rm_sta_cmd;
	struct iwl_rem_sta_resp *rem_sta_resp;

	struct iwl_host_cmd cmd = {
		.id = REPLY_REMOVE_STA,
		.len = { sizeof(struct iwl_rem_sta_cmd), },
		.data = { &rm_sta_cmd, },
	};

	memset(&rm_sta_cmd, 0, sizeof(rm_sta_cmd));
	rm_sta_cmd.num_sta = 1;
	memcpy(&rm_sta_cmd.addr, addr, ETH_ALEN);

	cmd.flags |= CMD_WANT_SKB;

	ret = iwl_dvm_send_cmd(priv, &cmd);

	if (ret)
		return ret;

	pkt = cmd.resp_pkt;
	rem_sta_resp = (void *)pkt->data;

	switch (rem_sta_resp->status) {
	case REM_STA_SUCCESS_MSK:
		if (!temporary) {
			spin_lock_bh(&priv->sta_lock);
			iwl_sta_ucode_deactivate(priv, sta_id);
			spin_unlock_bh(&priv->sta_lock);
		}
		IWL_DEBUG_ASSOC(priv, "REPLY_REMOVE_STA PASSED\n");
		break;
	default:
		ret = -EIO;
		IWL_ERR(priv, "REPLY_REMOVE_STA failed\n");
		break;
	}

	iwl_free_resp(&cmd);

	return ret;
}