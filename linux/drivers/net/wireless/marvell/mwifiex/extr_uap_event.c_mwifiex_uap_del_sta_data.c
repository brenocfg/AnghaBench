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
struct mwifiex_sta_node {int /*<<< orphan*/  mac_addr; scalar_t__ is_11n_enabled; } ;
struct mwifiex_private {scalar_t__ ap_11n_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  mwifiex_11n_del_rx_reorder_tbl_by_ta (struct mwifiex_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_del_sta_entry (struct mwifiex_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_del_tx_ba_stream_tbl_by_ra (struct mwifiex_private*,int /*<<< orphan*/ ) ; 

void mwifiex_uap_del_sta_data(struct mwifiex_private *priv,
			      struct mwifiex_sta_node *node)
{
	if (priv->ap_11n_enabled && node->is_11n_enabled) {
		mwifiex_11n_del_rx_reorder_tbl_by_ta(priv, node->mac_addr);
		mwifiex_del_tx_ba_stream_tbl_by_ra(priv, node->mac_addr);
	}
	mwifiex_del_sta_entry(priv, node->mac_addr);

	return;
}