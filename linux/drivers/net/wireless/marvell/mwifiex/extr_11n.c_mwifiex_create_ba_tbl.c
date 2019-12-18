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
struct mwifiex_tx_ba_stream_tbl {int tid; int ba_status; int /*<<< orphan*/  list; int /*<<< orphan*/  ra; } ;
struct mwifiex_ra_list_tbl {int ba_status; int amsdu_in_ampdu; } ;
struct mwifiex_private {int /*<<< orphan*/  tx_ba_stream_tbl_lock; int /*<<< orphan*/  tx_ba_stream_tbl_ptr; } ;
typedef  enum mwifiex_ba_status { ____Placeholder_mwifiex_ba_status } mwifiex_ba_status ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct mwifiex_tx_ba_stream_tbl* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_get_ba_tbl (struct mwifiex_private*,int,int /*<<< orphan*/ *) ; 
 int mwifiex_wmm_downgrade_tid (struct mwifiex_private*,int) ; 
 struct mwifiex_ra_list_tbl* mwifiex_wmm_get_ralist_node (struct mwifiex_private*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void mwifiex_create_ba_tbl(struct mwifiex_private *priv, u8 *ra, int tid,
			   enum mwifiex_ba_status ba_status)
{
	struct mwifiex_tx_ba_stream_tbl *new_node;
	struct mwifiex_ra_list_tbl *ra_list;
	int tid_down;

	if (!mwifiex_get_ba_tbl(priv, tid, ra)) {
		new_node = kzalloc(sizeof(struct mwifiex_tx_ba_stream_tbl),
				   GFP_ATOMIC);
		if (!new_node)
			return;

		tid_down = mwifiex_wmm_downgrade_tid(priv, tid);
		ra_list = mwifiex_wmm_get_ralist_node(priv, tid_down, ra);
		if (ra_list) {
			ra_list->ba_status = ba_status;
			ra_list->amsdu_in_ampdu = false;
		}
		INIT_LIST_HEAD(&new_node->list);

		new_node->tid = tid;
		new_node->ba_status = ba_status;
		memcpy(new_node->ra, ra, ETH_ALEN);

		spin_lock_bh(&priv->tx_ba_stream_tbl_lock);
		list_add_tail(&new_node->list, &priv->tx_ba_stream_tbl_ptr);
		spin_unlock_bh(&priv->tx_ba_stream_tbl_lock);
	}
}