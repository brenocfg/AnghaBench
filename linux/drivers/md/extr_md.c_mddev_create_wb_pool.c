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
struct wb_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ max_write_behind; } ;
struct mddev {int /*<<< orphan*/ * wb_info_pool; TYPE_1__ bitmap_info; } ;
struct md_rdev {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_WB_INFOS ; 
 int /*<<< orphan*/  WriteMostly ; 
 int /*<<< orphan*/  mddev_resume (struct mddev*) ; 
 int /*<<< orphan*/  mddev_suspend (struct mddev*) ; 
 int /*<<< orphan*/  memalloc_noio_restore (unsigned int) ; 
 unsigned int memalloc_noio_save () ; 
 int /*<<< orphan*/ * mempool_create_kmalloc_pool (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rdev_init_wb (struct md_rdev*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mddev_create_wb_pool(struct mddev *mddev, struct md_rdev *rdev,
			  bool is_suspend)
{
	if (mddev->bitmap_info.max_write_behind == 0)
		return;

	if (!test_bit(WriteMostly, &rdev->flags) || !rdev_init_wb(rdev))
		return;

	if (mddev->wb_info_pool == NULL) {
		unsigned int noio_flag;

		if (!is_suspend)
			mddev_suspend(mddev);
		noio_flag = memalloc_noio_save();
		mddev->wb_info_pool = mempool_create_kmalloc_pool(NR_WB_INFOS,
							sizeof(struct wb_info));
		memalloc_noio_restore(noio_flag);
		if (!mddev->wb_info_pool)
			pr_err("can't alloc memory pool for writemostly\n");
		if (!is_suspend)
			mddev_resume(mddev);
	}
}