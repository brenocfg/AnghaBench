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
typedef  enum mlxsw_reg_rtdp_type { ____Placeholder_mlxsw_reg_rtdp_type } mlxsw_reg_rtdp_type ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_rtdp_tunnel_index_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rtdp_type_set (char*,int) ; 
 int /*<<< orphan*/  rtdp ; 

__attribute__((used)) static inline void mlxsw_reg_rtdp_pack(char *payload,
				       enum mlxsw_reg_rtdp_type type,
				       u32 tunnel_index)
{
	MLXSW_REG_ZERO(rtdp, payload);
	mlxsw_reg_rtdp_type_set(payload, type);
	mlxsw_reg_rtdp_tunnel_index_set(payload, tunnel_index);
}