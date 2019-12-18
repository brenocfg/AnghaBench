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
struct reorder_tmr_cnxt {struct mwifiex_private* priv; struct mwifiex_rx_reorder_tbl* ptr; } ;
struct mwifiex_rx_reorder_tbl {int win_size; scalar_t__* rx_reorder_ptr; } ;
struct mwifiex_private {int /*<<< orphan*/  rx_reorder_tbl_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mwifiex_11n_find_last_seq_num(struct reorder_tmr_cnxt *ctx)
{
	struct mwifiex_rx_reorder_tbl *rx_reorder_tbl_ptr = ctx->ptr;
	struct mwifiex_private *priv = ctx->priv;
	int i;

	spin_lock_bh(&priv->rx_reorder_tbl_lock);
	for (i = rx_reorder_tbl_ptr->win_size - 1; i >= 0; --i) {
		if (rx_reorder_tbl_ptr->rx_reorder_ptr[i]) {
			spin_unlock_bh(&priv->rx_reorder_tbl_lock);
			return i;
		}
	}
	spin_unlock_bh(&priv->rx_reorder_tbl_lock);

	return -1;
}