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
struct ovl_priv_data {scalar_t__ enabled; } ;
struct omap_overlay_manager {int /*<<< orphan*/  overlays; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct omap_overlay {int /*<<< orphan*/  list; struct omap_overlay_manager* manager; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  apply_lock ; 
 int /*<<< orphan*/  data_lock ; 
 int /*<<< orphan*/  dispc_ovl_set_channel_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dispc_runtime_get () ; 
 int /*<<< orphan*/  dispc_runtime_put () ; 
 struct ovl_priv_data* get_ovl_priv (struct omap_overlay*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dss_ovl_set_manager(struct omap_overlay *ovl,
		struct omap_overlay_manager *mgr)
{
	struct ovl_priv_data *op = get_ovl_priv(ovl);
	unsigned long flags;
	int r;

	if (!mgr)
		return -EINVAL;

	mutex_lock(&apply_lock);

	if (ovl->manager) {
		DSSERR("overlay '%s' already has a manager '%s'\n",
				ovl->name, ovl->manager->name);
		r = -EINVAL;
		goto err;
	}

	r = dispc_runtime_get();
	if (r)
		goto err;

	spin_lock_irqsave(&data_lock, flags);

	if (op->enabled) {
		spin_unlock_irqrestore(&data_lock, flags);
		DSSERR("overlay has to be disabled to change the manager\n");
		r = -EINVAL;
		goto err1;
	}

	dispc_ovl_set_channel_out(ovl->id, mgr->id);

	ovl->manager = mgr;
	list_add_tail(&ovl->list, &mgr->overlays);

	spin_unlock_irqrestore(&data_lock, flags);

	dispc_runtime_put();

	mutex_unlock(&apply_lock);

	return 0;

err1:
	dispc_runtime_put();
err:
	mutex_unlock(&apply_lock);
	return r;
}