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
struct wsm_reset {int reset_statistics; } ;
struct TYPE_3__ {int /*<<< orphan*/  in_progress; } ;
struct cw1200_common {int join_pending; int delayed_unjoin; int delayed_link_loss; scalar_t__ join_status; int output_power; int disable_beacon_filter; int setbssparams_done; int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  firmware_ps_mode; int /*<<< orphan*/  bss_params; int /*<<< orphan*/  association_mode; int /*<<< orphan*/  listening; int /*<<< orphan*/  event_handler; scalar_t__ join_dtim_period; int /*<<< orphan*/  set_beacon_wakeup_period_work; int /*<<< orphan*/  update_filtering_work; TYPE_2__* hw; TYPE_1__ scan; int /*<<< orphan*/  join_timeout; } ;
struct TYPE_4__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 scalar_t__ CW1200_JOIN_STATUS_AP ; 
 scalar_t__ CW1200_JOIN_STATUS_PASSIVE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cw1200_cqm_bssloss_sm (struct cw1200_common*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cw1200_free_event_queue (struct cw1200_common*) ; 
 int /*<<< orphan*/  cw1200_setup_mac (struct cw1200_common*) ; 
 int /*<<< orphan*/  cw1200_update_filtering (struct cw1200_common*) ; 
 int /*<<< orphan*/  cw1200_update_listening (struct cw1200_common*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  wiphy_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wsm_flush_tx (struct cw1200_common*) ; 
 int /*<<< orphan*/  wsm_keep_alive_period (struct cw1200_common*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsm_reset (struct cw1200_common*,struct wsm_reset*) ; 
 int /*<<< orphan*/  wsm_set_block_ack_policy (struct cw1200_common*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsm_set_output_power (struct cw1200_common*,int) ; 

__attribute__((used)) static void cw1200_do_unjoin(struct cw1200_common *priv)
{
	struct wsm_reset reset = {
		.reset_statistics = true,
	};

	cancel_delayed_work_sync(&priv->join_timeout);

	mutex_lock(&priv->conf_mutex);
	priv->join_pending = false;

	if (atomic_read(&priv->scan.in_progress)) {
		if (priv->delayed_unjoin)
			wiphy_dbg(priv->hw->wiphy, "Delayed unjoin is already scheduled.\n");
		else
			priv->delayed_unjoin = true;
		goto done;
	}

	priv->delayed_link_loss = false;

	if (!priv->join_status)
		goto done;

	if (priv->join_status == CW1200_JOIN_STATUS_AP)
		goto done;

	cancel_work_sync(&priv->update_filtering_work);
	cancel_work_sync(&priv->set_beacon_wakeup_period_work);
	priv->join_status = CW1200_JOIN_STATUS_PASSIVE;

	/* Unjoin is a reset. */
	wsm_flush_tx(priv);
	wsm_keep_alive_period(priv, 0);
	wsm_reset(priv, &reset);
	wsm_set_output_power(priv, priv->output_power * 10);
	priv->join_dtim_period = 0;
	cw1200_setup_mac(priv);
	cw1200_free_event_queue(priv);
	cancel_work_sync(&priv->event_handler);
	cw1200_update_listening(priv, priv->listening);
	cw1200_cqm_bssloss_sm(priv, 0, 0, 0);

	/* Disable Block ACKs */
	wsm_set_block_ack_policy(priv, 0, 0);

	priv->disable_beacon_filter = false;
	cw1200_update_filtering(priv);
	memset(&priv->association_mode, 0,
	       sizeof(priv->association_mode));
	memset(&priv->bss_params, 0, sizeof(priv->bss_params));
	priv->setbssparams_done = false;
	memset(&priv->firmware_ps_mode, 0,
	       sizeof(priv->firmware_ps_mode));

	pr_debug("[STA] Unjoin completed.\n");

done:
	mutex_unlock(&priv->conf_mutex);
}