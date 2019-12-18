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
struct mlxsw_sp_rif {int /*<<< orphan*/  vr_id; int /*<<< orphan*/  rif_index; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_MAX_MTU ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_RITR_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_RITR_LOOPBACK_GENERIC ; 
 int /*<<< orphan*/  MLXSW_REG_RITR_LOOPBACK_IF ; 
 int /*<<< orphan*/  mlxsw_reg_ritr_loopback_protocol_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ritr_pack (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ritr ; 

__attribute__((used)) static int
mlxsw_sp_rif_ipip_lb_ul_rif_op(struct mlxsw_sp_rif *ul_rif, bool enable)
{
	struct mlxsw_sp *mlxsw_sp = ul_rif->mlxsw_sp;
	char ritr_pl[MLXSW_REG_RITR_LEN];

	mlxsw_reg_ritr_pack(ritr_pl, enable, MLXSW_REG_RITR_LOOPBACK_IF,
			    ul_rif->rif_index, ul_rif->vr_id, IP_MAX_MTU);
	mlxsw_reg_ritr_loopback_protocol_set(ritr_pl,
					     MLXSW_REG_RITR_LOOPBACK_GENERIC);

	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(ritr), ritr_pl);
}