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
typedef  scalar_t__ u8 ;
struct mlxsw_sp_vr {int dummy; } ;
struct mlxsw_sp_fib {TYPE_1__* lpm_tree; } ;
typedef  enum mlxsw_sp_l3proto { ____Placeholder_mlxsw_sp_l3proto } mlxsw_sp_l3proto ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 struct mlxsw_sp_fib* mlxsw_sp_vr_fib (struct mlxsw_sp_vr*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_vr_is_used (struct mlxsw_sp_vr*) ; 

__attribute__((used)) static bool
mlxsw_sp_vr_lpm_tree_should_replace(struct mlxsw_sp_vr *vr,
				    enum mlxsw_sp_l3proto proto, u8 tree_id)
{
	struct mlxsw_sp_fib *fib = mlxsw_sp_vr_fib(vr, proto);

	if (!mlxsw_sp_vr_is_used(vr))
		return false;
	if (fib->lpm_tree->id == tree_id)
		return true;
	return false;
}