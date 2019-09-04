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
struct mlxsw_afa_fwd_entry_ref {int /*<<< orphan*/  fwd_entry; int /*<<< orphan*/  resource; } ;
struct mlxsw_afa_block {int /*<<< orphan*/  afa; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlxsw_afa_fwd_entry_ref*) ; 
 int /*<<< orphan*/  mlxsw_afa_fwd_entry_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_afa_resource_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlxsw_afa_fwd_entry_ref_destroy(struct mlxsw_afa_block *block,
				struct mlxsw_afa_fwd_entry_ref *fwd_entry_ref)
{
	mlxsw_afa_resource_del(&fwd_entry_ref->resource);
	mlxsw_afa_fwd_entry_put(block->afa, fwd_entry_ref->fwd_entry);
	kfree(fwd_entry_ref);
}