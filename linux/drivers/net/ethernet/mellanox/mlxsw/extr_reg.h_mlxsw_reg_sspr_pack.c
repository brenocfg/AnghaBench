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

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_sspr_local_port_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sspr_m_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sspr_sub_port_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sspr_system_port_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sspr ; 

__attribute__((used)) static inline void mlxsw_reg_sspr_pack(char *payload, u8 local_port)
{
	MLXSW_REG_ZERO(sspr, payload);
	mlxsw_reg_sspr_m_set(payload, 1);
	mlxsw_reg_sspr_local_port_set(payload, local_port);
	mlxsw_reg_sspr_sub_port_set(payload, 0);
	mlxsw_reg_sspr_system_port_set(payload, local_port);
}