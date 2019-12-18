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
struct tegra_windowgroup {scalar_t__ usecount; int /*<<< orphan*/  lock; int /*<<< orphan*/  rst; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_windowgroup_enable(struct tegra_windowgroup *wgrp)
{
	mutex_lock(&wgrp->lock);

	if (wgrp->usecount == 0) {
		pm_runtime_get_sync(wgrp->parent);
		reset_control_deassert(wgrp->rst);
	}

	wgrp->usecount++;
	mutex_unlock(&wgrp->lock);

	return 0;
}