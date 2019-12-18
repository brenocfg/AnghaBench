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
struct ath6kl_vif {int /*<<< orphan*/  mc_filter; int /*<<< orphan*/  if_lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  sched_scan_timer; int /*<<< orphan*/  disconnect_timer; int /*<<< orphan*/  aggr_cntxt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WMM_ENABLED ; 
 int /*<<< orphan*/  aggr_init (struct ath6kl_vif*) ; 
 int /*<<< orphan*/  ath6kl_err (char*) ; 
 int /*<<< orphan*/  ath6kl_wmi_sscan_timer ; 
 int /*<<< orphan*/  disconnect_timer_handler ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_cfg80211_vif_init(struct ath6kl_vif *vif)
{
	vif->aggr_cntxt = aggr_init(vif);
	if (!vif->aggr_cntxt) {
		ath6kl_err("failed to initialize aggr\n");
		return -ENOMEM;
	}

	timer_setup(&vif->disconnect_timer, disconnect_timer_handler, 0);
	timer_setup(&vif->sched_scan_timer, ath6kl_wmi_sscan_timer, 0);

	set_bit(WMM_ENABLED, &vif->flags);
	spin_lock_init(&vif->if_lock);

	INIT_LIST_HEAD(&vif->mc_filter);

	return 0;
}