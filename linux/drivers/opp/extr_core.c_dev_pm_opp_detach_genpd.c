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
struct opp_table {int /*<<< orphan*/  genpd_virt_dev_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  _opp_detach_genpd (struct opp_table*) ; 
 int /*<<< orphan*/  dev_pm_opp_put_opp_table (struct opp_table*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void dev_pm_opp_detach_genpd(struct opp_table *opp_table)
{
	/*
	 * Acquire genpd_virt_dev_lock to make sure virt_dev isn't getting
	 * used in parallel.
	 */
	mutex_lock(&opp_table->genpd_virt_dev_lock);
	_opp_detach_genpd(opp_table);
	mutex_unlock(&opp_table->genpd_virt_dev_lock);

	dev_pm_opp_put_opp_table(opp_table);
}