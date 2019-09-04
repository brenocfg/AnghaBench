#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct mlxsw_sp_sb_cm {int dummy; } ;
struct mlxsw_sp {TYPE_2__* sb; } ;
typedef  enum mlxsw_reg_sbxx_dir { ____Placeholder_mlxsw_reg_sbxx_dir } mlxsw_reg_sbxx_dir ;
struct TYPE_4__ {TYPE_1__* ports; } ;
struct TYPE_3__ {struct mlxsw_sp_sb_cm** cms; } ;

/* Variables and functions */

__attribute__((used)) static struct mlxsw_sp_sb_cm *mlxsw_sp_sb_cm_get(struct mlxsw_sp *mlxsw_sp,
						 u8 local_port, u8 pg_buff,
						 enum mlxsw_reg_sbxx_dir dir)
{
	return &mlxsw_sp->sb->ports[local_port].cms[dir][pg_buff];
}