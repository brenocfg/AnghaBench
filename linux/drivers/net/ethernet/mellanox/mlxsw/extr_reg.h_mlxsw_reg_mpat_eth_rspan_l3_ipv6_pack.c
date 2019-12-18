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
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_MPAT_ETH_RSPAN_PROTOCOL_IPV6 ; 
 int /*<<< orphan*/  mlxsw_reg_mpat_eth_rspan_dip6_memcpy_to (char*,void*) ; 
 int /*<<< orphan*/  mlxsw_reg_mpat_eth_rspan_protocol_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mpat_eth_rspan_sip6_memcpy_to (char*,void*) ; 
 int /*<<< orphan*/  mlxsw_reg_mpat_eth_rspan_smac_memcpy_to (char*,char const*) ; 
 int /*<<< orphan*/  mlxsw_reg_mpat_eth_rspan_ttl_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
mlxsw_reg_mpat_eth_rspan_l3_ipv6_pack(char *payload, u8 ttl,
				      const char *smac,
				      struct in6_addr sip, struct in6_addr dip)
{
	mlxsw_reg_mpat_eth_rspan_ttl_set(payload, ttl);
	mlxsw_reg_mpat_eth_rspan_smac_memcpy_to(payload, smac);
	mlxsw_reg_mpat_eth_rspan_protocol_set(payload,
				    MLXSW_REG_MPAT_ETH_RSPAN_PROTOCOL_IPV6);
	mlxsw_reg_mpat_eth_rspan_sip6_memcpy_to(payload, (void *)&sip);
	mlxsw_reg_mpat_eth_rspan_dip6_memcpy_to(payload, (void *)&dip);
}