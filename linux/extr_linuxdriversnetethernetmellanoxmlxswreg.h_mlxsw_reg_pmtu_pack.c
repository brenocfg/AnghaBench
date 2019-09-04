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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_pmtu_admin_mtu_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pmtu_local_port_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pmtu_max_mtu_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pmtu_oper_mtu_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmtu ; 

__attribute__((used)) static inline void mlxsw_reg_pmtu_pack(char *payload, u8 local_port,
				       u16 new_mtu)
{
	MLXSW_REG_ZERO(pmtu, payload);
	mlxsw_reg_pmtu_local_port_set(payload, local_port);
	mlxsw_reg_pmtu_max_mtu_set(payload, 0);
	mlxsw_reg_pmtu_admin_mtu_set(payload, new_mtu);
	mlxsw_reg_pmtu_oper_mtu_set(payload, 0);
}