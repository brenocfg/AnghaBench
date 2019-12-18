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
typedef  scalar_t__ u16 ;
struct mlxsw_sp_fid_family {int /*<<< orphan*/  fids_bitmap; scalar_t__ start_index; TYPE_2__* ops; int /*<<< orphan*/  fids_list; int /*<<< orphan*/  fid_size; } ;
struct mlxsw_sp_fid {struct mlxsw_sp_fid_family* fid_family; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  list; int /*<<< orphan*/  ht_node; scalar_t__ fid_index; } ;
struct mlxsw_sp {TYPE_1__* fid_core; } ;
typedef  enum mlxsw_sp_fid_type { ____Placeholder_mlxsw_sp_fid_type } mlxsw_sp_fid_type ;
struct TYPE_4__ {int (* index_alloc ) (struct mlxsw_sp_fid*,void const*,scalar_t__*) ;int (* configure ) (struct mlxsw_sp_fid*) ;int /*<<< orphan*/  (* deconfigure ) (struct mlxsw_sp_fid*) ;int /*<<< orphan*/  (* setup ) (struct mlxsw_sp_fid*,void const*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  fid_ht; struct mlxsw_sp_fid_family** fid_family_arr; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlxsw_sp_fid* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_fid*) ; 
 struct mlxsw_sp_fid* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_ht_params ; 
 struct mlxsw_sp_fid* mlxsw_sp_fid_lookup (struct mlxsw_sp*,int,void const*) ; 
 int rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (struct mlxsw_sp_fid*,void const*,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (struct mlxsw_sp_fid*,void const*) ; 
 int stub3 (struct mlxsw_sp_fid*) ; 
 int /*<<< orphan*/  stub4 (struct mlxsw_sp_fid*) ; 

__attribute__((used)) static struct mlxsw_sp_fid *mlxsw_sp_fid_get(struct mlxsw_sp *mlxsw_sp,
					     enum mlxsw_sp_fid_type type,
					     const void *arg)
{
	struct mlxsw_sp_fid_family *fid_family;
	struct mlxsw_sp_fid *fid;
	u16 fid_index;
	int err;

	fid = mlxsw_sp_fid_lookup(mlxsw_sp, type, arg);
	if (fid)
		return fid;

	fid_family = mlxsw_sp->fid_core->fid_family_arr[type];
	fid = kzalloc(fid_family->fid_size, GFP_KERNEL);
	if (!fid)
		return ERR_PTR(-ENOMEM);
	fid->fid_family = fid_family;

	err = fid->fid_family->ops->index_alloc(fid, arg, &fid_index);
	if (err)
		goto err_index_alloc;
	fid->fid_index = fid_index;
	__set_bit(fid_index - fid_family->start_index, fid_family->fids_bitmap);

	if (fid->fid_family->ops->setup)
		fid->fid_family->ops->setup(fid, arg);

	err = fid->fid_family->ops->configure(fid);
	if (err)
		goto err_configure;

	err = rhashtable_insert_fast(&mlxsw_sp->fid_core->fid_ht, &fid->ht_node,
				     mlxsw_sp_fid_ht_params);
	if (err)
		goto err_rhashtable_insert;

	list_add(&fid->list, &fid_family->fids_list);
	fid->ref_count++;
	return fid;

err_rhashtable_insert:
	fid->fid_family->ops->deconfigure(fid);
err_configure:
	__clear_bit(fid_index - fid_family->start_index,
		    fid_family->fids_bitmap);
err_index_alloc:
	kfree(fid);
	return ERR_PTR(err);
}