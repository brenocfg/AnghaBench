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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_mprs_parsing_depth_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mprs_parsing_en_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_mprs_vxlan_udp_dport_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mprs ; 

__attribute__((used)) static inline void mlxsw_reg_mprs_pack(char *payload, u16 parsing_depth,
				       u16 vxlan_udp_dport)
{
	MLXSW_REG_ZERO(mprs, payload);
	mlxsw_reg_mprs_parsing_depth_set(payload, parsing_depth);
	mlxsw_reg_mprs_parsing_en_set(payload, true);
	mlxsw_reg_mprs_vxlan_udp_dport_set(payload, vxlan_udp_dport);
}