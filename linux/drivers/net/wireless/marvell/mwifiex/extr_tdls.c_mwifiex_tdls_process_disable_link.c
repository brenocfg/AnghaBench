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
typedef  int /*<<< orphan*/  u8 ;
struct mwifiex_sta_node {scalar_t__ is_11n_enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  ra_list_spinlock; } ;
struct mwifiex_private {TYPE_1__ wmm; } ;
struct mwifiex_ds_tdls_oper {int /*<<< orphan*/  tdls_action; int /*<<< orphan*/  peer_mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  HostCmd_ACT_GEN_SET ; 
 int /*<<< orphan*/  HostCmd_CMD_TDLS_OPER ; 
 int /*<<< orphan*/  MWIFIEX_TDLS_DISABLE_LINK ; 
 int /*<<< orphan*/  TDLS_LINK_TEARDOWN ; 
 int /*<<< orphan*/  TDLS_NOT_SETUP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mwifiex_ds_tdls_oper*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mwifiex_11n_cleanup_reorder_tbl (struct mwifiex_private*) ; 
 int /*<<< orphan*/  mwifiex_11n_delete_all_tx_ba_stream_tbl (struct mwifiex_private*) ; 
 int /*<<< orphan*/  mwifiex_auto_tdls_update_peer_status (struct mwifiex_private*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_del_sta_entry (struct mwifiex_private*,int /*<<< orphan*/  const*) ; 
 struct mwifiex_sta_node* mwifiex_get_sta_entry (struct mwifiex_private*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mwifiex_restore_tdls_packets (struct mwifiex_private*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mwifiex_ds_tdls_oper*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mwifiex_tdls_process_disable_link(struct mwifiex_private *priv, const u8 *peer)
{
	struct mwifiex_sta_node *sta_ptr;
	struct mwifiex_ds_tdls_oper tdls_oper;

	memset(&tdls_oper, 0, sizeof(struct mwifiex_ds_tdls_oper));
	sta_ptr = mwifiex_get_sta_entry(priv, peer);

	if (sta_ptr) {
		if (sta_ptr->is_11n_enabled) {
			mwifiex_11n_cleanup_reorder_tbl(priv);
			spin_lock_bh(&priv->wmm.ra_list_spinlock);
			mwifiex_11n_delete_all_tx_ba_stream_tbl(priv);
			spin_unlock_bh(&priv->wmm.ra_list_spinlock);
		}
		mwifiex_del_sta_entry(priv, peer);
	}

	mwifiex_restore_tdls_packets(priv, peer, TDLS_LINK_TEARDOWN);
	mwifiex_auto_tdls_update_peer_status(priv, peer, TDLS_NOT_SETUP);
	memcpy(&tdls_oper.peer_mac, peer, ETH_ALEN);
	tdls_oper.tdls_action = MWIFIEX_TDLS_DISABLE_LINK;
	return mwifiex_send_cmd(priv, HostCmd_CMD_TDLS_OPER,
				HostCmd_ACT_GEN_SET, 0, &tdls_oper, true);
}