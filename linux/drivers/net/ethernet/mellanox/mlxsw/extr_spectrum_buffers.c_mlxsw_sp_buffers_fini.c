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
struct mlxsw_sp {int /*<<< orphan*/  sb; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  devlink_sb_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_sb_ports_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  priv_to_devlink (int /*<<< orphan*/ ) ; 

void mlxsw_sp_buffers_fini(struct mlxsw_sp *mlxsw_sp)
{
	devlink_sb_unregister(priv_to_devlink(mlxsw_sp->core), 0);
	mlxsw_sp_sb_ports_fini(mlxsw_sp);
	kfree(mlxsw_sp->sb);
}