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
struct temp_data {int /*<<< orphan*/  attr_group; } ;
struct platform_data {struct temp_data** core_data; TYPE_1__* hwmon_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct temp_data*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void coretemp_remove_core(struct platform_data *pdata, int indx)
{
	struct temp_data *tdata = pdata->core_data[indx];

	/* Remove the sysfs attributes */
	sysfs_remove_group(&pdata->hwmon_dev->kobj, &tdata->attr_group);

	kfree(pdata->core_data[indx]);
	pdata->core_data[indx] = NULL;
}