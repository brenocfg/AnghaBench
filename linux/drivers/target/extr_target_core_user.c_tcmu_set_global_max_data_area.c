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
struct kernel_param {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TCMU_MBS_TO_BLOCKS (int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  global_db_count ; 
 int kstrtoint (char const*,int,int*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ tcmu_global_max_blocks ; 
 int /*<<< orphan*/  tcmu_unmap_work ; 

__attribute__((used)) static int tcmu_set_global_max_data_area(const char *str,
					 const struct kernel_param *kp)
{
	int ret, max_area_mb;

	ret = kstrtoint(str, 10, &max_area_mb);
	if (ret)
		return -EINVAL;

	if (max_area_mb <= 0) {
		pr_err("global_max_data_area must be larger than 0.\n");
		return -EINVAL;
	}

	tcmu_global_max_blocks = TCMU_MBS_TO_BLOCKS(max_area_mb);
	if (atomic_read(&global_db_count) > tcmu_global_max_blocks)
		schedule_delayed_work(&tcmu_unmap_work, 0);
	else
		cancel_delayed_work_sync(&tcmu_unmap_work);

	return 0;
}