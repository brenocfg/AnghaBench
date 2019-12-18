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
typedef  scalar_t__ u16 ;
struct mlxsw_sp_fid_family {size_t type; int /*<<< orphan*/  fids_bitmap; scalar_t__ flood_tables; int /*<<< orphan*/  fids_list; struct mlxsw_sp* mlxsw_sp; scalar_t__ start_index; scalar_t__ end_index; } ;
struct mlxsw_sp {TYPE_1__* fid_core; } ;
struct TYPE_2__ {struct mlxsw_sp_fid_family** fid_family_arr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_zalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_fid_family*) ; 
 struct mlxsw_sp_fid_family* kmemdup (struct mlxsw_sp_fid_family const*,int,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_fid_flood_tables_init (struct mlxsw_sp_fid_family*) ; 

__attribute__((used)) static int mlxsw_sp_fid_family_register(struct mlxsw_sp *mlxsw_sp,
					const struct mlxsw_sp_fid_family *tmpl)
{
	u16 nr_fids = tmpl->end_index - tmpl->start_index + 1;
	struct mlxsw_sp_fid_family *fid_family;
	int err;

	fid_family = kmemdup(tmpl, sizeof(*fid_family), GFP_KERNEL);
	if (!fid_family)
		return -ENOMEM;

	fid_family->mlxsw_sp = mlxsw_sp;
	INIT_LIST_HEAD(&fid_family->fids_list);
	fid_family->fids_bitmap = bitmap_zalloc(nr_fids, GFP_KERNEL);
	if (!fid_family->fids_bitmap) {
		err = -ENOMEM;
		goto err_alloc_fids_bitmap;
	}

	if (fid_family->flood_tables) {
		err = mlxsw_sp_fid_flood_tables_init(fid_family);
		if (err)
			goto err_fid_flood_tables_init;
	}

	mlxsw_sp->fid_core->fid_family_arr[tmpl->type] = fid_family;

	return 0;

err_fid_flood_tables_init:
	bitmap_free(fid_family->fids_bitmap);
err_alloc_fids_bitmap:
	kfree(fid_family);
	return err;
}