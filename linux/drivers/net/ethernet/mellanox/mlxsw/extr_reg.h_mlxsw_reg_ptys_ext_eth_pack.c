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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_PTYS_PROTO_MASK_ETH ; 
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ptys_an_disable_admin_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_ptys_ext_eth_proto_admin_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ptys_local_port_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ptys_proto_mask_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptys ; 

__attribute__((used)) static inline void mlxsw_reg_ptys_ext_eth_pack(char *payload, u8 local_port,
					       u32 proto_admin, bool autoneg)
{
	MLXSW_REG_ZERO(ptys, payload);
	mlxsw_reg_ptys_local_port_set(payload, local_port);
	mlxsw_reg_ptys_proto_mask_set(payload, MLXSW_REG_PTYS_PROTO_MASK_ETH);
	mlxsw_reg_ptys_ext_eth_proto_admin_set(payload, proto_admin);
	mlxsw_reg_ptys_an_disable_admin_set(payload, !autoneg);
}