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
struct TYPE_2__ {int /*<<< orphan*/  pg_wq; int /*<<< orphan*/  free_list; int /*<<< orphan*/  page_root; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 

int mlx5_pagealloc_init(struct mlx5_core_dev *dev)
{
	dev->priv.page_root = RB_ROOT;
	INIT_LIST_HEAD(&dev->priv.free_list);
	dev->priv.pg_wq = create_singlethread_workqueue("mlx5_page_allocator");
	if (!dev->priv.pg_wq)
		return -ENOMEM;

	return 0;
}