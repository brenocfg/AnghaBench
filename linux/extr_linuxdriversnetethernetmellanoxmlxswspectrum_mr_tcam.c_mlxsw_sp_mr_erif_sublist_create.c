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
struct mlxsw_sp_mr_tcam_erif_list {int /*<<< orphan*/  erif_sublists; } ;
struct mlxsw_sp_mr_erif_sublist {int /*<<< orphan*/  list; int /*<<< orphan*/  rigr2_kvdl_index; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlxsw_sp_mr_erif_sublist* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLXSW_SP_KVDL_ENTRY_TYPE_MCRIGR ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_mr_erif_sublist*) ; 
 struct mlxsw_sp_mr_erif_sublist* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mlxsw_sp_kvdl_alloc (struct mlxsw_sp*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlxsw_sp_mr_erif_sublist *
mlxsw_sp_mr_erif_sublist_create(struct mlxsw_sp *mlxsw_sp,
				struct mlxsw_sp_mr_tcam_erif_list *erif_list)
{
	struct mlxsw_sp_mr_erif_sublist *erif_sublist;
	int err;

	erif_sublist = kzalloc(sizeof(*erif_sublist), GFP_KERNEL);
	if (!erif_sublist)
		return ERR_PTR(-ENOMEM);
	err = mlxsw_sp_kvdl_alloc(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_MCRIGR,
				  1, &erif_sublist->rigr2_kvdl_index);
	if (err) {
		kfree(erif_sublist);
		return ERR_PTR(err);
	}

	list_add_tail(&erif_sublist->list, &erif_list->erif_sublists);
	return erif_sublist;
}