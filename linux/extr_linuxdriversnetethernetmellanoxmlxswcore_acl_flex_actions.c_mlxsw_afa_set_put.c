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
struct mlxsw_afa_set {scalar_t__ shared; scalar_t__ ref_count; } ;
struct mlxsw_afa {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_afa_set_destroy (struct mlxsw_afa_set*) ; 
 int /*<<< orphan*/  mlxsw_afa_set_unshare (struct mlxsw_afa*,struct mlxsw_afa_set*) ; 

__attribute__((used)) static void mlxsw_afa_set_put(struct mlxsw_afa *mlxsw_afa,
			      struct mlxsw_afa_set *set)
{
	if (--set->ref_count)
		return;
	if (set->shared)
		mlxsw_afa_set_unshare(mlxsw_afa, set);
	mlxsw_afa_set_destroy(set);
}