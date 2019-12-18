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
struct mlxsw_sp_nve_mc_record {int dummy; } ;
struct mlxsw_sp_nve_mc_entry {int /*<<< orphan*/  addr4; } ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_tnumt_udip_set (char*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp_nve_mc_record_ipv4_entry_set(const struct mlxsw_sp_nve_mc_record *mc_record,
				      const struct mlxsw_sp_nve_mc_entry *mc_entry,
				      char *tnumt_pl, unsigned int entry_index)
{
	u32 udip = be32_to_cpu(mc_entry->addr4);

	mlxsw_reg_tnumt_udip_set(tnumt_pl, entry_index, udip);
}