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
struct opp_table {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct opp_table*) ; 
 int /*<<< orphan*/  _add_opp_dev_unlocked (struct device*,struct opp_table*) ; 
 struct opp_table* _allocate_opp_table (struct device*,int) ; 
 struct opp_table* _find_opp_table_unlocked (struct device*) ; 
 struct opp_table* _managed_opp (struct device*,int) ; 
 int /*<<< orphan*/  dev_pm_opp_put_opp_table (struct opp_table*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opp_table_lock ; 

__attribute__((used)) static struct opp_table *_opp_get_opp_table(struct device *dev, int index)
{
	struct opp_table *opp_table;

	/* Hold our table modification lock here */
	mutex_lock(&opp_table_lock);

	opp_table = _find_opp_table_unlocked(dev);
	if (!IS_ERR(opp_table))
		goto unlock;

	opp_table = _managed_opp(dev, index);
	if (opp_table) {
		if (!_add_opp_dev_unlocked(dev, opp_table)) {
			dev_pm_opp_put_opp_table(opp_table);
			opp_table = NULL;
		}
		goto unlock;
	}

	opp_table = _allocate_opp_table(dev, index);

unlock:
	mutex_unlock(&opp_table_lock);

	return opp_table;
}