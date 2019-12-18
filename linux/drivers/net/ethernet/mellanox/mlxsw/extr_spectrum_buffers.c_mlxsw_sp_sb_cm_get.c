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
typedef  size_t u8 ;
struct mlxsw_sp_sb_port {struct mlxsw_sp_sb_cm* eg_cms; struct mlxsw_sp_sb_cm* ing_cms; } ;
struct mlxsw_sp_sb_cm {int dummy; } ;
struct mlxsw_sp {TYPE_1__* sb; } ;
typedef  enum mlxsw_reg_sbxx_dir { ____Placeholder_mlxsw_reg_sbxx_dir } mlxsw_reg_sbxx_dir ;
struct TYPE_2__ {struct mlxsw_sp_sb_port* ports; } ;

/* Variables and functions */
 int MLXSW_REG_SBXX_DIR_INGRESS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mlxsw_sp_sb_cm_exists (size_t,int) ; 

__attribute__((used)) static struct mlxsw_sp_sb_cm *mlxsw_sp_sb_cm_get(struct mlxsw_sp *mlxsw_sp,
						 u8 local_port, u8 pg_buff,
						 enum mlxsw_reg_sbxx_dir dir)
{
	struct mlxsw_sp_sb_port *sb_port = &mlxsw_sp->sb->ports[local_port];

	WARN_ON(!mlxsw_sp_sb_cm_exists(pg_buff, dir));
	if (dir == MLXSW_REG_SBXX_DIR_INGRESS)
		return &sb_port->ing_cms[pg_buff];
	else
		return &sb_port->eg_cms[pg_buff];
}