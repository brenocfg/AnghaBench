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
struct mlxsw_sp {int /*<<< orphan*/  afa; int /*<<< orphan*/  afa_ops; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_ACTIONS_PER_SET ; 
 int /*<<< orphan*/  MLXSW_CORE_RES_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_afa_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlxsw_sp*) ; 

int mlxsw_sp_afa_init(struct mlxsw_sp *mlxsw_sp)
{
	mlxsw_sp->afa = mlxsw_afa_create(MLXSW_CORE_RES_GET(mlxsw_sp->core,
							    ACL_ACTIONS_PER_SET),
					 mlxsw_sp->afa_ops, mlxsw_sp);
	return PTR_ERR_OR_ZERO(mlxsw_sp->afa);
}