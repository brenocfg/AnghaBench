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
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_REG_FLOW_COUNTER_SET_TYPE_PACKETS_BYTES ; 
 int MLXSW_REG_MGPC_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_MGPC_OPCODE_CLEAR ; 
 int /*<<< orphan*/  mgpc ; 
 int /*<<< orphan*/  mlxsw_reg_mgpc_pack (char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mlxsw_sp_flow_counter_clear(struct mlxsw_sp *mlxsw_sp,
				       unsigned int counter_index)
{
	char mgpc_pl[MLXSW_REG_MGPC_LEN];

	mlxsw_reg_mgpc_pack(mgpc_pl, counter_index, MLXSW_REG_MGPC_OPCODE_CLEAR,
			    MLXSW_REG_FLOW_COUNTER_SET_TYPE_PACKETS_BYTES);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(mgpc), mgpc_pl);
}