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
union mlxsw_sp_l3addr {scalar_t__ addr4; } ;
struct mlxsw_sp_nve_mc_record {int dummy; } ;
struct mlxsw_sp_nve_mc_entry {scalar_t__ addr4; } ;

/* Variables and functions */

__attribute__((used)) static bool
mlxsw_sp_nve_mc_record_ipv4_entry_compare(const struct mlxsw_sp_nve_mc_record *mc_record,
					  const struct mlxsw_sp_nve_mc_entry *mc_entry,
					  const union mlxsw_sp_l3addr *addr)
{
	return mc_entry->addr4 == addr->addr4;
}