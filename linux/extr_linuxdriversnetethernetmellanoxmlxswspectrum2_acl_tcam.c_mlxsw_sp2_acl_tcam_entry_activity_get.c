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
struct mlxsw_sp2_acl_tcam_entry {int /*<<< orphan*/  act_block; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int mlxsw_afa_block_activity_get (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
mlxsw_sp2_acl_tcam_entry_activity_get(struct mlxsw_sp *mlxsw_sp,
				      void *region_priv, void *entry_priv,
				      bool *activity)
{
	struct mlxsw_sp2_acl_tcam_entry *entry = entry_priv;

	return mlxsw_afa_block_activity_get(entry->act_block, activity);
}