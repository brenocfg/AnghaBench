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
struct omap_overlay_manager {int /*<<< orphan*/  id; } ;
struct mgr_priv_data {int enabled; int updating; } ;

/* Variables and functions */
 int /*<<< orphan*/  apply_lock ; 
 int /*<<< orphan*/  data_lock ; 
 int /*<<< orphan*/  dispc_mgr_disable_sync (int /*<<< orphan*/ ) ; 
 struct mgr_priv_data* get_mgr_priv (struct omap_overlay_manager*) ; 
 int /*<<< orphan*/  mgr_manual_update (struct omap_overlay_manager*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_pending_extra_info_updates () ; 

__attribute__((used)) static void dss_mgr_disable_compat(struct omap_overlay_manager *mgr)
{
	struct mgr_priv_data *mp = get_mgr_priv(mgr);
	unsigned long flags;

	mutex_lock(&apply_lock);

	if (!mp->enabled)
		goto out;

	wait_pending_extra_info_updates();

	if (!mgr_manual_update(mgr))
		dispc_mgr_disable_sync(mgr->id);

	spin_lock_irqsave(&data_lock, flags);

	mp->updating = false;
	mp->enabled = false;

	spin_unlock_irqrestore(&data_lock, flags);

out:
	mutex_unlock(&apply_lock);
}