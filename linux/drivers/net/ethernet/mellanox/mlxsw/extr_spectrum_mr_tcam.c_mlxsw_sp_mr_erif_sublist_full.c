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
struct mlxsw_sp_mr_erif_sublist {int num_erifs; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC_ERIF_LIST_ENTRIES ; 
 int MLXSW_CORE_RES_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
mlxsw_sp_mr_erif_sublist_full(struct mlxsw_sp *mlxsw_sp,
			      struct mlxsw_sp_mr_erif_sublist *erif_sublist)
{
	int erif_list_entries = MLXSW_CORE_RES_GET(mlxsw_sp->core,
						   MC_ERIF_LIST_ENTRIES);

	return erif_sublist->num_erifs == erif_list_entries;
}