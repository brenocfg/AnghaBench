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
struct mlxsw_sp_fid_family {size_t type; int /*<<< orphan*/  fids_list; int /*<<< orphan*/  fids_bitmap; } ;
struct mlxsw_sp {TYPE_1__* fid_core; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** fid_family_arr; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  bitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_fid_family*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlxsw_sp_fid_family_unregister(struct mlxsw_sp *mlxsw_sp,
			       struct mlxsw_sp_fid_family *fid_family)
{
	mlxsw_sp->fid_core->fid_family_arr[fid_family->type] = NULL;
	bitmap_free(fid_family->fids_bitmap);
	WARN_ON_ONCE(!list_empty(&fid_family->fids_list));
	kfree(fid_family);
}