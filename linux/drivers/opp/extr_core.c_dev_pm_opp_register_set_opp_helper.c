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
struct opp_table {int (* set_opp ) (struct dev_pm_set_opp_data*) ;int /*<<< orphan*/  opp_list; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct opp_table* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 struct opp_table* dev_pm_opp_get_opp_table (struct device*) ; 
 int /*<<< orphan*/  dev_pm_opp_put_opp_table (struct opp_table*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

struct opp_table *dev_pm_opp_register_set_opp_helper(struct device *dev,
			int (*set_opp)(struct dev_pm_set_opp_data *data))
{
	struct opp_table *opp_table;

	if (!set_opp)
		return ERR_PTR(-EINVAL);

	opp_table = dev_pm_opp_get_opp_table(dev);
	if (!opp_table)
		return ERR_PTR(-ENOMEM);

	/* This should be called before OPPs are initialized */
	if (WARN_ON(!list_empty(&opp_table->opp_list))) {
		dev_pm_opp_put_opp_table(opp_table);
		return ERR_PTR(-EBUSY);
	}

	/* Another CPU that shares the OPP table has set the helper ? */
	if (!opp_table->set_opp)
		opp_table->set_opp = set_opp;

	return opp_table;
}