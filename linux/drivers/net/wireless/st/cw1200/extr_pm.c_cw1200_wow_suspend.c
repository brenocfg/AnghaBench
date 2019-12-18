#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_hw {struct cw1200_common* priv; } ;
struct cw1200_suspend_state {scalar_t__ prev_ps_mode; int beacon_skipping; void* link_id_gc; void* direct_probe; void* join_tmo; void* bss_loss_tmo; } ;
struct cw1200_pm_state {struct cw1200_suspend_state* suspend_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  stay_awake; } ;
struct TYPE_13__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  probe_work; } ;
struct TYPE_15__ {scalar_t__ mode; } ;
struct TYPE_9__ {scalar_t__ num_queued; } ;
struct cw1200_common {scalar_t__ join_status; int join_dtim_period; int /*<<< orphan*/  conf_mutex; TYPE_5__ scan; int /*<<< orphan*/  link_id_gc_work; int /*<<< orphan*/  join_timeout; int /*<<< orphan*/  bss_loss_work; int /*<<< orphan*/  bh_rx; TYPE_4__* hw; int /*<<< orphan*/  hwbus_priv; TYPE_3__* hwbus_ops; int /*<<< orphan*/  mcast_timeout; int /*<<< orphan*/  has_multicast_subscription; int /*<<< orphan*/  recent_scan; int /*<<< orphan*/  clear_recent_scan_work; int /*<<< orphan*/  ps_mode_switch_in_progress; int /*<<< orphan*/  ps_mode_switch_done; TYPE_7__ powersave_mode; TYPE_2__* vif; int /*<<< orphan*/  hw_bufs_used; int /*<<< orphan*/  bh_evt_wq; scalar_t__ join_pending; scalar_t__ channel_switch_in_progress; TYPE_1__ tx_queue_stats; struct cw1200_pm_state pm_state; } ;
struct cfg80211_wowlan {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_14__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_12__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_11__ {int (* power_mgmt ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  p2p; } ;

/* Variables and functions */
 int CW1200_BEACON_SKIPPING_MULTIPLIER ; 
 scalar_t__ CW1200_JOIN_STATUS_STA ; 
 int EAGAIN ; 
 int EBUSY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ WSM_PSM_PS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cw1200_bh_resume (struct cw1200_common*) ; 
 scalar_t__ cw1200_bh_suspend (struct cw1200_common*) ; 
 int /*<<< orphan*/  cw1200_ether_type_filter_off ; 
 TYPE_8__ cw1200_ether_type_filter_on ; 
 int /*<<< orphan*/  cw1200_resume_work (struct cw1200_common*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  cw1200_set_pm (struct cw1200_common*,TYPE_7__*) ; 
 void* cw1200_suspend_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cw1200_udp_port_filter_off ; 
 TYPE_6__ cw1200_udp_port_filter_on ; 
 int /*<<< orphan*/  cw1200_wow_resume (struct ieee80211_hw*) ; 
 scalar_t__ down_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cw1200_suspend_state*) ; 
 struct cw1200_suspend_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 
 int timer_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 scalar_t__ wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wsm_lock_tx_async (struct cw1200_common*) ; 
 int /*<<< orphan*/  wsm_set_beacon_wakeup_period (struct cw1200_common*,int,int) ; 
 int /*<<< orphan*/  wsm_set_ether_type_filter (struct cw1200_common*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wsm_set_udp_port_filter (struct cw1200_common*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wsm_unlock_tx (struct cw1200_common*) ; 

int cw1200_wow_suspend(struct ieee80211_hw *hw, struct cfg80211_wowlan *wowlan)
{
	struct cw1200_common *priv = hw->priv;
	struct cw1200_pm_state *pm_state = &priv->pm_state;
	struct cw1200_suspend_state *state;
	int ret;

	spin_lock_bh(&pm_state->lock);
	ret = timer_pending(&pm_state->stay_awake);
	spin_unlock_bh(&pm_state->lock);
	if (ret)
		return -EAGAIN;

	/* Do not suspend when datapath is not idle */
	if (priv->tx_queue_stats.num_queued)
		return -EBUSY;

	/* Make sure there is no configuration requests in progress. */
	if (!mutex_trylock(&priv->conf_mutex))
		return -EBUSY;

	/* Ensure pending operations are done.
	 * Note also that wow_suspend must return in ~2.5sec, before
	 * watchdog is triggered.
	 */
	if (priv->channel_switch_in_progress)
		goto revert1;

	/* Do not suspend when join is pending */
	if (priv->join_pending)
		goto revert1;

	/* Do not suspend when scanning */
	if (down_trylock(&priv->scan.lock))
		goto revert1;

	/* Lock TX. */
	wsm_lock_tx_async(priv);

	/* Wait to avoid possible race with bh code.
	 * But do not wait too long...
	 */
	if (wait_event_timeout(priv->bh_evt_wq,
			       !priv->hw_bufs_used, HZ / 10) <= 0)
		goto revert2;

	/* Set UDP filter */
	wsm_set_udp_port_filter(priv, &cw1200_udp_port_filter_on.hdr);

	/* Set ethernet frame type filter */
	wsm_set_ether_type_filter(priv, &cw1200_ether_type_filter_on.hdr);

	/* Allocate state */
	state = kzalloc(sizeof(struct cw1200_suspend_state), GFP_KERNEL);
	if (!state)
		goto revert3;

	/* Change to legacy PS while going to suspend */
	if (!priv->vif->p2p &&
	    priv->join_status == CW1200_JOIN_STATUS_STA &&
	    priv->powersave_mode.mode != WSM_PSM_PS) {
		state->prev_ps_mode = priv->powersave_mode.mode;
		priv->powersave_mode.mode = WSM_PSM_PS;
		cw1200_set_pm(priv, &priv->powersave_mode);
		if (wait_event_interruptible_timeout(priv->ps_mode_switch_done,
						     !priv->ps_mode_switch_in_progress, 1*HZ) <= 0) {
			goto revert4;
		}
	}

	/* Store delayed work states. */
	state->bss_loss_tmo =
		cw1200_suspend_work(&priv->bss_loss_work);
	state->join_tmo =
		cw1200_suspend_work(&priv->join_timeout);
	state->direct_probe =
		cw1200_suspend_work(&priv->scan.probe_work);
	state->link_id_gc =
		cw1200_suspend_work(&priv->link_id_gc_work);

	cancel_delayed_work_sync(&priv->clear_recent_scan_work);
	atomic_set(&priv->recent_scan, 0);

	/* Enable beacon skipping */
	if (priv->join_status == CW1200_JOIN_STATUS_STA &&
	    priv->join_dtim_period &&
	    !priv->has_multicast_subscription) {
		state->beacon_skipping = true;
		wsm_set_beacon_wakeup_period(priv,
					     priv->join_dtim_period,
					     CW1200_BEACON_SKIPPING_MULTIPLIER * priv->join_dtim_period);
	}

	/* Stop serving thread */
	if (cw1200_bh_suspend(priv))
		goto revert5;

	ret = timer_pending(&priv->mcast_timeout);
	if (ret)
		goto revert6;

	/* Store suspend state */
	pm_state->suspend_state = state;

	/* Enable IRQ wake */
	ret = priv->hwbus_ops->power_mgmt(priv->hwbus_priv, true);
	if (ret) {
		wiphy_err(priv->hw->wiphy,
			  "PM request failed: %d. WoW is disabled.\n", ret);
		cw1200_wow_resume(hw);
		return -EBUSY;
	}

	/* Force resume if event is coming from the device. */
	if (atomic_read(&priv->bh_rx)) {
		cw1200_wow_resume(hw);
		return -EAGAIN;
	}

	return 0;

revert6:
	WARN_ON(cw1200_bh_resume(priv));
revert5:
	cw1200_resume_work(priv, &priv->bss_loss_work,
			   state->bss_loss_tmo);
	cw1200_resume_work(priv, &priv->join_timeout,
			   state->join_tmo);
	cw1200_resume_work(priv, &priv->scan.probe_work,
			   state->direct_probe);
	cw1200_resume_work(priv, &priv->link_id_gc_work,
			   state->link_id_gc);
revert4:
	kfree(state);
revert3:
	wsm_set_udp_port_filter(priv, &cw1200_udp_port_filter_off);
	wsm_set_ether_type_filter(priv, &cw1200_ether_type_filter_off);
revert2:
	wsm_unlock_tx(priv);
	up(&priv->scan.lock);
revert1:
	mutex_unlock(&priv->conf_mutex);
	return -EBUSY;
}