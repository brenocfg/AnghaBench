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
struct mlx5dr_table {TYPE_2__* dmn; TYPE_1__* miss_action; int /*<<< orphan*/  refcount; } ;
struct TYPE_4__ {int /*<<< orphan*/  refcount; } ;
struct TYPE_3__ {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int EBUSY ; 
 int dr_table_destroy_sw_owned_tbl (struct mlx5dr_table*) ; 
 int /*<<< orphan*/  dr_table_uninit (struct mlx5dr_table*) ; 
 int /*<<< orphan*/  kfree (struct mlx5dr_table*) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 

int mlx5dr_table_destroy(struct mlx5dr_table *tbl)
{
	int ret;

	if (refcount_read(&tbl->refcount) > 1)
		return -EBUSY;

	ret = dr_table_destroy_sw_owned_tbl(tbl);
	if (ret)
		return ret;

	dr_table_uninit(tbl);

	if (tbl->miss_action)
		refcount_dec(&tbl->miss_action->refcount);

	refcount_dec(&tbl->dmn->refcount);
	kfree(tbl);

	return ret;
}