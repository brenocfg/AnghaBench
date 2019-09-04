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
 int /*<<< orphan*/  MLXSW_REG_RATR_IPIP_TYPE_IPV4 ; 
 int /*<<< orphan*/  mlxsw_reg_ratr_ipip_ipv4_udip_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ratr_ipip_type_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlxsw_reg_ratr_ipip4_entry_pack(char *payload, u32 ipv4_udip)
{
	mlxsw_reg_ratr_ipip_type_set(payload, MLXSW_REG_RATR_IPIP_TYPE_IPV4);
	mlxsw_reg_ratr_ipip_ipv4_udip_set(payload, ipv4_udip);
}