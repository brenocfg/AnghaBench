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
struct ieee80211_hw {struct cw1200_common* priv; } ;
struct cw1200_suspend_state {int beacon_skipping; int /*<<< orphan*/  link_id_gc; int /*<<< orphan*/  direct_probe; int /*<<< orphan*/  join_tmo; int /*<<< orphan*/  bss_loss_tmo; int /*<<< orphan*/  prev_ps_mode; } ;
struct cw1200_pm_state {struct cw1200_suspend_state* suspend_state; } ;
struct TYPE_7__ {int /*<<< orphan*/  probe_work; int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {int /*<<< orphan*/  mode; } ;
struct cw1200_common {scalar_t__ join_status; int beacon_int; int join_dtim_period; int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  link_id_gc_work; TYPE_3__ scan; int /*<<< orphan*/  join_timeout; int /*<<< orphan*/  bss_loss_work; TYPE_4__ powersave_mode; TYPE_2__* vif; int /*<<< orphan*/  hwbus_priv; TYPE_1__* hwbus_ops; struct cw1200_pm_state pm_state; } ;
struct TYPE_6__ {int /*<<< orphan*/  p2p; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* power_mgmt ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 scalar_t__ CW1200_JOIN_STATUS_STA ; 
 int MAX_BEACON_SKIP_TIME_MS ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cw1200_bh_resume (struct cw1200_common*) ; 
 int /*<<< orphan*/  cw1200_ether_type_filter_off ; 
 int /*<<< orphan*/  cw1200_resume_work (struct cw1200_common*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cw1200_set_pm (struct cw1200_common*,TYPE_4__*) ; 
 int /*<<< orphan*/  cw1200_udp_port_filter_off ; 
 int /*<<< orphan*/  kfree (struct cw1200_suspend_state*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wsm_set_beacon_wakeup_period (struct cw1200_common*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsm_set_ether_type_filter (struct cw1200_common*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wsm_set_udp_port_filter (struct cw1200_common*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wsm_unlock_tx (struct cw1200_common*) ; 

int cw1200_wow_resume(struct ieee80211_hw *hw)
{
	struct cw1200_common *priv = hw->priv;
	struct cw1200_pm_state *pm_state = &priv->pm_state;
	struct cw1200_suspend_state *state;

	state = pm_state->suspend_state;
	pm_state->suspend_state = NULL;

	/* Disable IRQ wake */
	priv->hwbus_ops->power_mgmt(priv->hwbus_priv, false);

	/* Scan.lock must be released before BH is resumed other way
	 * in case when BSS_LOST command arrived the processing of the
	 * command will be delayed.
	 */
	up(&priv->scan.lock);

	/* Resume BH thread */
	WARN_ON(cw1200_bh_resume(priv));

	/* Restores previous PS mode */
	if (!priv->vif->p2p && priv->join_status == CW1200_JOIN_STATUS_STA) {
		priv->powersave_mode.mode = state->prev_ps_mode;
		cw1200_set_pm(priv, &priv->powersave_mode);
	}

	if (state->beacon_skipping) {
		wsm_set_beacon_wakeup_period(priv, priv->beacon_int *
					     priv->join_dtim_period >
					     MAX_BEACON_SKIP_TIME_MS ? 1 :
					     priv->join_dtim_period, 0);
		state->beacon_skipping = false;
	}

	/* Resume delayed work */
	cw1200_resume_work(priv, &priv->bss_loss_work,
			   state->bss_loss_tmo);
	cw1200_resume_work(priv, &priv->join_timeout,
			   state->join_tmo);
	cw1200_resume_work(priv, &priv->scan.probe_work,
			   state->direct_probe);
	cw1200_resume_work(priv, &priv->link_id_gc_work,
			   state->link_id_gc);

	/* Remove UDP port filter */
	wsm_set_udp_port_filter(priv, &cw1200_udp_port_filter_off);

	/* Remove ethernet frame type filter */
	wsm_set_ether_type_filter(priv, &cw1200_ether_type_filter_off);

	/* Unlock datapath */
	wsm_unlock_tx(priv);

	/* Unlock configuration mutex */
	mutex_unlock(&priv->conf_mutex);

	/* Free memory */
	kfree(state);

	return 0;
}