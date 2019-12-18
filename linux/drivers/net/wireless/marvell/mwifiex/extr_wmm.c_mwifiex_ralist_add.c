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
typedef  int /*<<< orphan*/  u8 ;
struct mwifiex_sta_node {int /*<<< orphan*/  max_amsdu; int /*<<< orphan*/  tx_pause; } ;
struct mwifiex_ra_list_tbl {int tdls_link; int amsdu_in_ampdu; int /*<<< orphan*/  list; int /*<<< orphan*/  ba_packet_thr; scalar_t__ ba_pkt_count; scalar_t__ is_11n_enabled; int /*<<< orphan*/  max_amsdu; int /*<<< orphan*/  tx_paused; int /*<<< orphan*/  ba_status; } ;
struct TYPE_4__ {TYPE_1__* tid_tbl_ptr; } ;
struct mwifiex_private {TYPE_2__ wmm; int /*<<< orphan*/  sta_list_spinlock; struct mwifiex_adapter* adapter; } ;
struct mwifiex_adapter {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ra_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA_SETUP_NONE ; 
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  INFO ; 
 scalar_t__ IS_11N_ENABLED (struct mwifiex_private*) ; 
 int MAX_NUM_TID ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,struct mwifiex_ra_list_tbl*,...) ; 
 int /*<<< orphan*/  mwifiex_get_random_ba_threshold () ; 
 struct mwifiex_sta_node* mwifiex_get_sta_entry (struct mwifiex_private*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mwifiex_get_tdls_link_status (struct mwifiex_private*,int /*<<< orphan*/  const*) ; 
 scalar_t__ mwifiex_is_sta_11n_enabled (struct mwifiex_private*,struct mwifiex_sta_node*) ; 
 scalar_t__ mwifiex_is_tdls_link_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_queuing_ra_based (struct mwifiex_private*) ; 
 scalar_t__ mwifiex_tdls_peer_11n_enabled (struct mwifiex_private*,int /*<<< orphan*/  const*) ; 
 struct mwifiex_ra_list_tbl* mwifiex_wmm_allocate_ralist_node (struct mwifiex_adapter*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void mwifiex_ralist_add(struct mwifiex_private *priv, const u8 *ra)
{
	int i;
	struct mwifiex_ra_list_tbl *ra_list;
	struct mwifiex_adapter *adapter = priv->adapter;
	struct mwifiex_sta_node *node;


	for (i = 0; i < MAX_NUM_TID; ++i) {
		ra_list = mwifiex_wmm_allocate_ralist_node(adapter, ra);
		mwifiex_dbg(adapter, INFO,
			    "info: created ra_list %p\n", ra_list);

		if (!ra_list)
			break;

		ra_list->is_11n_enabled = 0;
		ra_list->tdls_link = false;
		ra_list->ba_status = BA_SETUP_NONE;
		ra_list->amsdu_in_ampdu = false;
		if (!mwifiex_queuing_ra_based(priv)) {
			if (mwifiex_is_tdls_link_setup
				(mwifiex_get_tdls_link_status(priv, ra))) {
				ra_list->tdls_link = true;
				ra_list->is_11n_enabled =
					mwifiex_tdls_peer_11n_enabled(priv, ra);
			} else {
				ra_list->is_11n_enabled = IS_11N_ENABLED(priv);
			}
		} else {
			spin_lock_bh(&priv->sta_list_spinlock);
			node = mwifiex_get_sta_entry(priv, ra);
			if (node)
				ra_list->tx_paused = node->tx_pause;
			ra_list->is_11n_enabled =
				      mwifiex_is_sta_11n_enabled(priv, node);
			if (ra_list->is_11n_enabled)
				ra_list->max_amsdu = node->max_amsdu;
			spin_unlock_bh(&priv->sta_list_spinlock);
		}

		mwifiex_dbg(adapter, DATA, "data: ralist %p: is_11n_enabled=%d\n",
			    ra_list, ra_list->is_11n_enabled);

		if (ra_list->is_11n_enabled) {
			ra_list->ba_pkt_count = 0;
			ra_list->ba_packet_thr =
					      mwifiex_get_random_ba_threshold();
		}
		list_add_tail(&ra_list->list,
			      &priv->wmm.tid_tbl_ptr[i].ra_list);
	}
}