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

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_ptys_eth_proto_admin_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ptys_eth_proto_cap_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ptys_eth_proto_oper_get (char*) ; 

__attribute__((used)) static inline void mlxsw_reg_ptys_eth_unpack(char *payload,
					     u32 *p_eth_proto_cap,
					     u32 *p_eth_proto_admin,
					     u32 *p_eth_proto_oper)
{
	if (p_eth_proto_cap)
		*p_eth_proto_cap =
			mlxsw_reg_ptys_eth_proto_cap_get(payload);
	if (p_eth_proto_admin)
		*p_eth_proto_admin =
			mlxsw_reg_ptys_eth_proto_admin_get(payload);
	if (p_eth_proto_oper)
		*p_eth_proto_oper =
			mlxsw_reg_ptys_eth_proto_oper_get(payload);
}