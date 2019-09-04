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
typedef  unsigned long u8 ;
struct xpc_vars_sn2 {unsigned long heartbeat; unsigned long vars_part_pa; unsigned long activate_IRQ_nasid; unsigned long activate_IRQ_phys_cpuid; unsigned long amos_page_pa; unsigned long version; } ;
struct xpc_partition_sn2 {unsigned long remote_vars_pa; unsigned long remote_vars_part_pa; unsigned long activate_IRQ_nasid; unsigned long activate_IRQ_phys_cpuid; unsigned long remote_amos_page_pa; unsigned long remote_vars_version; } ;
struct TYPE_2__ {struct xpc_partition_sn2 sn2; } ;
struct xpc_partition {unsigned long remote_rp_version; unsigned long remote_rp_ts_jiffies; unsigned long remote_rp_pa; unsigned long last_heartbeat; TYPE_1__ sn; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  xpc_part ; 

__attribute__((used)) static void
xpc_update_partition_info_sn2(struct xpc_partition *part, u8 remote_rp_version,
			      unsigned long *remote_rp_ts_jiffies,
			      unsigned long remote_rp_pa,
			      unsigned long remote_vars_pa,
			      struct xpc_vars_sn2 *remote_vars)
{
	struct xpc_partition_sn2 *part_sn2 = &part->sn.sn2;

	part->remote_rp_version = remote_rp_version;
	dev_dbg(xpc_part, "  remote_rp_version = 0x%016x\n",
		part->remote_rp_version);

	part->remote_rp_ts_jiffies = *remote_rp_ts_jiffies;
	dev_dbg(xpc_part, "  remote_rp_ts_jiffies = 0x%016lx\n",
		part->remote_rp_ts_jiffies);

	part->remote_rp_pa = remote_rp_pa;
	dev_dbg(xpc_part, "  remote_rp_pa = 0x%016lx\n", part->remote_rp_pa);

	part_sn2->remote_vars_pa = remote_vars_pa;
	dev_dbg(xpc_part, "  remote_vars_pa = 0x%016lx\n",
		part_sn2->remote_vars_pa);

	part->last_heartbeat = remote_vars->heartbeat - 1;
	dev_dbg(xpc_part, "  last_heartbeat = 0x%016llx\n",
		part->last_heartbeat);

	part_sn2->remote_vars_part_pa = remote_vars->vars_part_pa;
	dev_dbg(xpc_part, "  remote_vars_part_pa = 0x%016lx\n",
		part_sn2->remote_vars_part_pa);

	part_sn2->activate_IRQ_nasid = remote_vars->activate_IRQ_nasid;
	dev_dbg(xpc_part, "  activate_IRQ_nasid = 0x%x\n",
		part_sn2->activate_IRQ_nasid);

	part_sn2->activate_IRQ_phys_cpuid =
	    remote_vars->activate_IRQ_phys_cpuid;
	dev_dbg(xpc_part, "  activate_IRQ_phys_cpuid = 0x%x\n",
		part_sn2->activate_IRQ_phys_cpuid);

	part_sn2->remote_amos_page_pa = remote_vars->amos_page_pa;
	dev_dbg(xpc_part, "  remote_amos_page_pa = 0x%lx\n",
		part_sn2->remote_amos_page_pa);

	part_sn2->remote_vars_version = remote_vars->version;
	dev_dbg(xpc_part, "  remote_vars_version = 0x%x\n",
		part_sn2->remote_vars_version);
}