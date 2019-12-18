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
struct mlxsw_sp_acl_erp_core {int /*<<< orphan*/  erp_tables; int /*<<< orphan*/  bf; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_bf_fini (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp_acl_erp_tables_fini(struct mlxsw_sp *mlxsw_sp,
					 struct mlxsw_sp_acl_erp_core *erp_core)
{
	mlxsw_sp_acl_bf_fini(erp_core->bf);
	gen_pool_destroy(erp_core->erp_tables);
}