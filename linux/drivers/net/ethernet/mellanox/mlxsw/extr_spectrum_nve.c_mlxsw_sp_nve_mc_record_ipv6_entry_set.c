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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp_nve_mc_record {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr6_kvdl_index; } ;
struct mlxsw_sp_nve_mc_entry {TYPE_1__ ipv6_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_tnumt_udip_ptr_set (char*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp_nve_mc_record_ipv6_entry_set(const struct mlxsw_sp_nve_mc_record *mc_record,
				      const struct mlxsw_sp_nve_mc_entry *mc_entry,
				      char *tnumt_pl, unsigned int entry_index)
{
	u32 udip_ptr = mc_entry->ipv6_entry.addr6_kvdl_index;

	mlxsw_reg_tnumt_udip_ptr_set(tnumt_pl, entry_index, udip_ptr);
}