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
 int ENODEV ; 
 scalar_t__ IS_ERR (struct opp_table*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct device*) ; 
 int PTR_ERR (struct opp_table*) ; 
 int /*<<< orphan*/  WARN (int,char*,char*,int) ; 
 struct opp_table* _find_opp_table (struct device*) ; 
 int /*<<< orphan*/  _put_opp_list_kref (struct opp_table*) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_pm_opp_put_opp_table (struct opp_table*) ; 

void _dev_pm_opp_find_and_remove_table(struct device *dev)
{
	struct opp_table *opp_table;

	/* Check for existing table for 'dev' */
	opp_table = _find_opp_table(dev);
	if (IS_ERR(opp_table)) {
		int error = PTR_ERR(opp_table);

		if (error != -ENODEV)
			WARN(1, "%s: opp_table: %d\n",
			     IS_ERR_OR_NULL(dev) ?
					"Invalid device" : dev_name(dev),
			     error);
		return;
	}

	_put_opp_list_kref(opp_table);

	/* Drop reference taken by _find_opp_table() */
	dev_pm_opp_put_opp_table(opp_table);

	/* Drop reference taken while the OPP table was added */
	dev_pm_opp_put_opp_table(opp_table);
}