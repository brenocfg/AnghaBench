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
typedef  int /*<<< orphan*/  u64 ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_REG_FLOW_COUNTER_SET_TYPE_PACKETS_BYTES ; 
 int MLXSW_REG_MGPC_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_MGPC_OPCODE_NOP ; 
 int /*<<< orphan*/  mgpc ; 
 int /*<<< orphan*/  mlxsw_reg_mgpc_byte_counter_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_mgpc_pack (char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mgpc_packet_counter_get (char*) ; 
 int mlxsw_reg_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int mlxsw_sp_flow_counter_get(struct mlxsw_sp *mlxsw_sp,
			      unsigned int counter_index, u64 *packets,
			      u64 *bytes)
{
	char mgpc_pl[MLXSW_REG_MGPC_LEN];
	int err;

	mlxsw_reg_mgpc_pack(mgpc_pl, counter_index, MLXSW_REG_MGPC_OPCODE_NOP,
			    MLXSW_REG_FLOW_COUNTER_SET_TYPE_PACKETS_BYTES);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(mgpc), mgpc_pl);
	if (err)
		return err;
	if (packets)
		*packets = mlxsw_reg_mgpc_packet_counter_get(mgpc_pl);
	if (bytes)
		*bytes = mlxsw_reg_mgpc_byte_counter_get(mgpc_pl);
	return 0;
}