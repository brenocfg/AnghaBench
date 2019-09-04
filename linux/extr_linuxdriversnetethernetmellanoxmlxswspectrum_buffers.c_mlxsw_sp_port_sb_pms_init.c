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
struct mlxsw_sp_port {int /*<<< orphan*/  local_port; int /*<<< orphan*/  mlxsw_sp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_SBXX_DIR_EGRESS ; 
 int /*<<< orphan*/  MLXSW_REG_SBXX_DIR_INGRESS ; 
 int /*<<< orphan*/  MLXSW_SP_SB_PMS_EGRESS_LEN ; 
 int /*<<< orphan*/  MLXSW_SP_SB_PMS_INGRESS_LEN ; 
 int __mlxsw_sp_port_sb_pms_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_sb_pms_egress ; 
 int /*<<< orphan*/  mlxsw_sp_sb_pms_ingress ; 

__attribute__((used)) static int mlxsw_sp_port_sb_pms_init(struct mlxsw_sp_port *mlxsw_sp_port)
{
	int err;

	err = __mlxsw_sp_port_sb_pms_init(mlxsw_sp_port->mlxsw_sp,
					  mlxsw_sp_port->local_port,
					  MLXSW_REG_SBXX_DIR_INGRESS,
					  mlxsw_sp_sb_pms_ingress,
					  MLXSW_SP_SB_PMS_INGRESS_LEN);
	if (err)
		return err;
	return __mlxsw_sp_port_sb_pms_init(mlxsw_sp_port->mlxsw_sp,
					   mlxsw_sp_port->local_port,
					   MLXSW_REG_SBXX_DIR_EGRESS,
					   mlxsw_sp_sb_pms_egress,
					   MLXSW_SP_SB_PMS_EGRESS_LEN);
}