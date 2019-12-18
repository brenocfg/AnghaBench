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
typedef  enum mlxsw_reg_tnpc_tunnel_port { ____Placeholder_mlxsw_reg_tnpc_tunnel_port } mlxsw_reg_tnpc_tunnel_port ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_tnpc_learn_enable_v4_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_tnpc_learn_enable_v6_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_tnpc_tunnel_port_set (char*,int) ; 
 int /*<<< orphan*/  tnpc ; 

__attribute__((used)) static inline void mlxsw_reg_tnpc_pack(char *payload,
				       enum mlxsw_reg_tnpc_tunnel_port tport,
				       bool learn_enable)
{
	MLXSW_REG_ZERO(tnpc, payload);
	mlxsw_reg_tnpc_tunnel_port_set(payload, tport);
	mlxsw_reg_tnpc_learn_enable_v4_set(payload, learn_enable);
	mlxsw_reg_tnpc_learn_enable_v6_set(payload, learn_enable);
}