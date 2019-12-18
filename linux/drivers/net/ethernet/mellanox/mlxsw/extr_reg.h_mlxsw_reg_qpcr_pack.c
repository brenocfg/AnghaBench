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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  enum mlxsw_reg_qpcr_ir_units { ____Placeholder_mlxsw_reg_qpcr_ir_units } mlxsw_reg_qpcr_ir_units ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_QPCR_ACTION_DISCARD ; 
 int /*<<< orphan*/  MLXSW_REG_QPCR_G_GLOBAL ; 
 int /*<<< orphan*/  MLXSW_REG_QPCR_RATE_TYPE_SINGLE ; 
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_qpcr_bytes_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_qpcr_cbs_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_qpcr_cir_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_qpcr_g_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_qpcr_ir_units_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_qpcr_pid_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_qpcr_rate_type_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_qpcr_violate_action_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qpcr ; 

__attribute__((used)) static inline void mlxsw_reg_qpcr_pack(char *payload, u16 pid,
				       enum mlxsw_reg_qpcr_ir_units ir_units,
				       bool bytes, u32 cir, u16 cbs)
{
	MLXSW_REG_ZERO(qpcr, payload);
	mlxsw_reg_qpcr_pid_set(payload, pid);
	mlxsw_reg_qpcr_g_set(payload, MLXSW_REG_QPCR_G_GLOBAL);
	mlxsw_reg_qpcr_rate_type_set(payload, MLXSW_REG_QPCR_RATE_TYPE_SINGLE);
	mlxsw_reg_qpcr_violate_action_set(payload,
					  MLXSW_REG_QPCR_ACTION_DISCARD);
	mlxsw_reg_qpcr_cir_set(payload, cir);
	mlxsw_reg_qpcr_ir_units_set(payload, ir_units);
	mlxsw_reg_qpcr_bytes_set(payload, bytes);
	mlxsw_reg_qpcr_cbs_set(payload, cbs);
}