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
struct TYPE_2__ {int /*<<< orphan*/  min_time_window_attr; int /*<<< orphan*/  max_time_window_attr; int /*<<< orphan*/  min_power_attr; int /*<<< orphan*/  max_power_attr; int /*<<< orphan*/  name_attr; int /*<<< orphan*/  time_window_attr; int /*<<< orphan*/  power_limit_attr; } ;

/* Variables and functions */
 int MAX_CONSTRAINTS_PER_ZONE ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 TYPE_1__* constraint_attrs ; 
 int create_constraint_attribute (int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_constraint_attributes () ; 
 int /*<<< orphan*/  show_constraint_max_power_uw ; 
 int /*<<< orphan*/  show_constraint_max_time_window_us ; 
 int /*<<< orphan*/  show_constraint_min_power_uw ; 
 int /*<<< orphan*/  show_constraint_min_time_window_us ; 
 int /*<<< orphan*/  show_constraint_name ; 
 int /*<<< orphan*/  show_constraint_power_limit_uw ; 
 int /*<<< orphan*/  show_constraint_time_window_us ; 
 int /*<<< orphan*/ * store_constraint_power_limit_uw ; 
 int /*<<< orphan*/ * store_constraint_time_window_us ; 

__attribute__((used)) static int seed_constraint_attributes(void)
{
	int i;
	int ret;

	for (i = 0; i < MAX_CONSTRAINTS_PER_ZONE; ++i) {
		ret = create_constraint_attribute(i, "power_limit_uw",
					S_IWUSR | S_IRUGO,
					&constraint_attrs[i].power_limit_attr,
					show_constraint_power_limit_uw,
					store_constraint_power_limit_uw);
		if (ret)
			goto err_alloc;
		ret = create_constraint_attribute(i, "time_window_us",
					S_IWUSR | S_IRUGO,
					&constraint_attrs[i].time_window_attr,
					show_constraint_time_window_us,
					store_constraint_time_window_us);
		if (ret)
			goto err_alloc;
		ret = create_constraint_attribute(i, "name", S_IRUGO,
				&constraint_attrs[i].name_attr,
				show_constraint_name,
				NULL);
		if (ret)
			goto err_alloc;
		ret = create_constraint_attribute(i, "max_power_uw", S_IRUGO,
				&constraint_attrs[i].max_power_attr,
				show_constraint_max_power_uw,
				NULL);
		if (ret)
			goto err_alloc;
		ret = create_constraint_attribute(i, "min_power_uw", S_IRUGO,
				&constraint_attrs[i].min_power_attr,
				show_constraint_min_power_uw,
				NULL);
		if (ret)
			goto err_alloc;
		ret = create_constraint_attribute(i, "max_time_window_us",
				S_IRUGO,
				&constraint_attrs[i].max_time_window_attr,
				show_constraint_max_time_window_us,
				NULL);
		if (ret)
			goto err_alloc;
		ret = create_constraint_attribute(i, "min_time_window_us",
				S_IRUGO,
				&constraint_attrs[i].min_time_window_attr,
				show_constraint_min_time_window_us,
				NULL);
		if (ret)
			goto err_alloc;

	}

	return 0;

err_alloc:
	free_constraint_attributes();

	return ret;
}