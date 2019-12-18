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
struct tegra_windowgroup {int usecount; int /*<<< orphan*/  lock; int /*<<< orphan*/  parent; int /*<<< orphan*/  index; int /*<<< orphan*/  rst; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_windowgroup_disable(struct tegra_windowgroup *wgrp)
{
	int err;

	mutex_lock(&wgrp->lock);

	if (wgrp->usecount == 1) {
		err = reset_control_assert(wgrp->rst);
		if (err < 0) {
			pr_err("failed to assert reset for window group %u\n",
			       wgrp->index);
		}

		pm_runtime_put(wgrp->parent);
	}

	wgrp->usecount--;
	mutex_unlock(&wgrp->lock);
}