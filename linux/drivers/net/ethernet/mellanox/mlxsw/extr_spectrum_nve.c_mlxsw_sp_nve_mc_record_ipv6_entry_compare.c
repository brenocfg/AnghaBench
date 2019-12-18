#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union mlxsw_sp_l3addr {int /*<<< orphan*/  addr6; } ;
struct mlxsw_sp_nve_mc_record {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr6; } ;
struct mlxsw_sp_nve_mc_entry {TYPE_1__ ipv6_entry; } ;

/* Variables and functions */
 int ipv6_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
mlxsw_sp_nve_mc_record_ipv6_entry_compare(const struct mlxsw_sp_nve_mc_record *mc_record,
					  const struct mlxsw_sp_nve_mc_entry *mc_entry,
					  const union mlxsw_sp_l3addr *addr)
{
	return ipv6_addr_equal(&mc_entry->ipv6_entry.addr6, &addr->addr6);
}