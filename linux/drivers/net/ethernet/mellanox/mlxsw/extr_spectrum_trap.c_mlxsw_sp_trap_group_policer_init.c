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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct devlink_trap_group {int id; } ;
typedef  enum mlxsw_reg_qpcr_ir_units { ____Placeholder_mlxsw_reg_qpcr_ir_units } mlxsw_reg_qpcr_ir_units ;

/* Variables and functions */
#define  DEVLINK_TRAP_GROUP_GENERIC_ID_L2_DROPS 128 
 int EINVAL ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_QPCR_IR_UNITS_M ; 
 int MLXSW_REG_QPCR_LEN ; 
 int /*<<< orphan*/  MLXSW_SP_DISCARD_POLICER_ID ; 
 int /*<<< orphan*/  mlxsw_reg_qpcr_pack (char*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  qpcr ; 

__attribute__((used)) static int
mlxsw_sp_trap_group_policer_init(struct mlxsw_sp *mlxsw_sp,
				 const struct devlink_trap_group *group)
{
	enum mlxsw_reg_qpcr_ir_units ir_units;
	char qpcr_pl[MLXSW_REG_QPCR_LEN];
	u16 policer_id;
	u8 burst_size;
	bool is_bytes;
	u32 rate;

	switch (group->id) {
	case DEVLINK_TRAP_GROUP_GENERIC_ID_L2_DROPS:
		policer_id = MLXSW_SP_DISCARD_POLICER_ID;
		ir_units = MLXSW_REG_QPCR_IR_UNITS_M;
		is_bytes = false;
		rate = 10 * 1024; /* 10Kpps */
		burst_size = 7;
		break;
	default:
		return -EINVAL;
	}

	mlxsw_reg_qpcr_pack(qpcr_pl, policer_id, ir_units, is_bytes, rate,
			    burst_size);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(qpcr), qpcr_pl);
}