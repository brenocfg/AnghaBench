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
struct iwl_scale_tbl_info {int /*<<< orphan*/  current_rate; } ;
struct iwl_rxon_context {int dummy; } ;
struct iwl_priv {int bt_full_concurrent; scalar_t__ bt_traffic_load; scalar_t__ last_bt_traffic_load; int /*<<< orphan*/  bt_full_concurrency; int /*<<< orphan*/  workqueue; scalar_t__ bt_ant_couple_ok; scalar_t__ bt_ci_compliance; } ;
struct iwl_lq_sta {size_t active_tbl; int /*<<< orphan*/  lq; struct iwl_scale_tbl_info* lq_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ASYNC ; 
 int /*<<< orphan*/  iwl_send_lq_cmd (struct iwl_priv*,struct iwl_rxon_context*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rs_fill_link_cmd (struct iwl_priv*,struct iwl_lq_sta*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rs_bt_update_lq(struct iwl_priv *priv, struct iwl_rxon_context *ctx,
			    struct iwl_lq_sta *lq_sta)
{
	struct iwl_scale_tbl_info *tbl;
	bool full_concurrent = priv->bt_full_concurrent;

	if (priv->bt_ant_couple_ok) {
		/*
		 * Is there a need to switch between
		 * full concurrency and 3-wire?
		 */
		if (priv->bt_ci_compliance && priv->bt_ant_couple_ok)
			full_concurrent = true;
		else
			full_concurrent = false;
	}
	if ((priv->bt_traffic_load != priv->last_bt_traffic_load) ||
	    (priv->bt_full_concurrent != full_concurrent)) {
		priv->bt_full_concurrent = full_concurrent;
		priv->last_bt_traffic_load = priv->bt_traffic_load;

		/* Update uCode's rate table. */
		tbl = &(lq_sta->lq_info[lq_sta->active_tbl]);
		rs_fill_link_cmd(priv, lq_sta, tbl->current_rate);
		iwl_send_lq_cmd(priv, ctx, &lq_sta->lq, CMD_ASYNC, false);

		queue_work(priv->workqueue, &priv->bt_full_concurrency);
	}
}