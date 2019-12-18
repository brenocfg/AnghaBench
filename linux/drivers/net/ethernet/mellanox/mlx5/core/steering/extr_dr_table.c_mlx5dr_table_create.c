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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5dr_table {int /*<<< orphan*/  refcount; int /*<<< orphan*/  level; struct mlx5dr_domain* dmn; } ;
struct mlx5dr_domain {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int dr_table_create_sw_owned_tbl (struct mlx5dr_table*) ; 
 int dr_table_init (struct mlx5dr_table*) ; 
 int /*<<< orphan*/  dr_table_uninit (struct mlx5dr_table*) ; 
 int /*<<< orphan*/  kfree (struct mlx5dr_table*) ; 
 struct mlx5dr_table* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

struct mlx5dr_table *mlx5dr_table_create(struct mlx5dr_domain *dmn, u32 level)
{
	struct mlx5dr_table *tbl;
	int ret;

	refcount_inc(&dmn->refcount);

	tbl = kzalloc(sizeof(*tbl), GFP_KERNEL);
	if (!tbl)
		goto dec_ref;

	tbl->dmn = dmn;
	tbl->level = level;
	refcount_set(&tbl->refcount, 1);

	ret = dr_table_init(tbl);
	if (ret)
		goto free_tbl;

	ret = dr_table_create_sw_owned_tbl(tbl);
	if (ret)
		goto uninit_tbl;

	return tbl;

uninit_tbl:
	dr_table_uninit(tbl);
free_tbl:
	kfree(tbl);
dec_ref:
	refcount_dec(&dmn->refcount);
	return NULL;
}