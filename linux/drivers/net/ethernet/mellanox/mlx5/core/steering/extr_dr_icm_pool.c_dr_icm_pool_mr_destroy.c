#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5dr_icm_dm {int /*<<< orphan*/  obj_id; int /*<<< orphan*/  addr; int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
struct mlx5dr_icm_mr {int /*<<< orphan*/  mkey; int /*<<< orphan*/  mr_list; struct mlx5dr_icm_dm dm; TYPE_2__* pool; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dmn; } ;
struct TYPE_3__ {struct mlx5_core_dev* mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (struct mlx5dr_icm_mr*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_destroy_mkey (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_dm_sw_icm_dealloc (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dr_icm_pool_mr_destroy(struct mlx5dr_icm_mr *icm_mr)
{
	struct mlx5_core_dev *mdev = icm_mr->pool->dmn->mdev;
	struct mlx5dr_icm_dm *dm = &icm_mr->dm;

	list_del(&icm_mr->mr_list);
	mlx5_core_destroy_mkey(mdev, &icm_mr->mkey);
	mlx5_dm_sw_icm_dealloc(mdev, dm->type, dm->length, 0,
			       dm->addr, dm->obj_id);
	kvfree(icm_mr);
}