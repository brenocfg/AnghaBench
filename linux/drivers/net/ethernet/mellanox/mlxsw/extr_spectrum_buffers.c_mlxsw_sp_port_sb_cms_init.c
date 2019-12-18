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
struct mlxsw_sp_port {int /*<<< orphan*/  local_port; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {TYPE_1__* sb_vals; } ;
struct TYPE_2__ {int /*<<< orphan*/  cms_egress_count; int /*<<< orphan*/  cms_egress; int /*<<< orphan*/  cms_ingress_count; int /*<<< orphan*/  cms_ingress; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_SBXX_DIR_EGRESS ; 
 int /*<<< orphan*/  MLXSW_REG_SBXX_DIR_INGRESS ; 
 int __mlxsw_sp_sb_cms_init (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_port_sb_cms_init(struct mlxsw_sp_port *mlxsw_sp_port)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	int err;

	err = __mlxsw_sp_sb_cms_init(mlxsw_sp,
				     mlxsw_sp_port->local_port,
				     MLXSW_REG_SBXX_DIR_INGRESS,
				     mlxsw_sp->sb_vals->cms_ingress,
				     mlxsw_sp->sb_vals->cms_ingress_count);
	if (err)
		return err;
	return __mlxsw_sp_sb_cms_init(mlxsw_sp_port->mlxsw_sp,
				      mlxsw_sp_port->local_port,
				      MLXSW_REG_SBXX_DIR_EGRESS,
				      mlxsw_sp->sb_vals->cms_egress,
				      mlxsw_sp->sb_vals->cms_egress_count);
}