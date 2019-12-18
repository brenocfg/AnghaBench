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
struct mlxsw_afa_fwd_entry {scalar_t__ ref_count; } ;
struct mlxsw_afa {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_afa_fwd_entry_destroy (struct mlxsw_afa*,struct mlxsw_afa_fwd_entry*) ; 

__attribute__((used)) static void mlxsw_afa_fwd_entry_put(struct mlxsw_afa *mlxsw_afa,
				    struct mlxsw_afa_fwd_entry *fwd_entry)
{
	if (--fwd_entry->ref_count)
		return;
	mlxsw_afa_fwd_entry_destroy(mlxsw_afa, fwd_entry);
}