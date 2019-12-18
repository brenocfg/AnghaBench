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
typedef  enum mlxsw_reg_mpat_eth_rspan_version { ____Placeholder_mlxsw_reg_mpat_eth_rspan_version } mlxsw_reg_mpat_eth_rspan_version ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_mpat_eth_rspan_mac_memcpy_to (char*,char const*) ; 
 int /*<<< orphan*/  mlxsw_reg_mpat_eth_rspan_tp_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_mpat_eth_rspan_version_set (char*,int) ; 

__attribute__((used)) static inline void
mlxsw_reg_mpat_eth_rspan_l2_pack(char *payload,
				 enum mlxsw_reg_mpat_eth_rspan_version version,
				 const char *mac,
				 bool tp)
{
	mlxsw_reg_mpat_eth_rspan_version_set(payload, version);
	mlxsw_reg_mpat_eth_rspan_mac_memcpy_to(payload, mac);
	mlxsw_reg_mpat_eth_rspan_tp_set(payload, tp);
}