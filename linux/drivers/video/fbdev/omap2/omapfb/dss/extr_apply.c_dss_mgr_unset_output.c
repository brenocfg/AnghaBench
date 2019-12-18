#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct omap_overlay_manager {TYPE_1__* output; } ;
struct mgr_priv_data {scalar_t__ enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/ * manager; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  apply_lock ; 
 int /*<<< orphan*/  data_lock ; 
 struct mgr_priv_data* get_mgr_priv (struct omap_overlay_manager*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dss_mgr_unset_output(struct omap_overlay_manager *mgr)
{
	int r;
	struct mgr_priv_data *mp = get_mgr_priv(mgr);
	unsigned long flags;

	mutex_lock(&apply_lock);

	if (!mgr->output) {
		DSSERR("failed to unset output, output not set\n");
		r = -EINVAL;
		goto err;
	}

	spin_lock_irqsave(&data_lock, flags);

	if (mp->enabled) {
		DSSERR("output can't be unset when manager is enabled\n");
		r = -EINVAL;
		goto err1;
	}

	spin_unlock_irqrestore(&data_lock, flags);

	mgr->output->manager = NULL;
	mgr->output = NULL;

	mutex_unlock(&apply_lock);

	return 0;
err1:
	spin_unlock_irqrestore(&data_lock, flags);
err:
	mutex_unlock(&apply_lock);

	return r;
}