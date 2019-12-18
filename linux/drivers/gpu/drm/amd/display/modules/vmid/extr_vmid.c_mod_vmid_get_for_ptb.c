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
typedef  unsigned int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct mod_vmid {int dummy; } ;
struct dc_virtual_addr_space_config {int /*<<< orphan*/  page_table_base_addr; } ;
struct core_vmid {scalar_t__ num_vmids_available; int /*<<< orphan*/  dc; struct dc_virtual_addr_space_config base_config; } ;

/* Variables and functions */
 struct core_vmid* MOD_VMID_TO_CORE (struct mod_vmid*) ; 
 int /*<<< orphan*/  add_ptb_to_table (struct core_vmid*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_setup_vm_context (int /*<<< orphan*/ ,struct dc_virtual_addr_space_config*,unsigned int) ; 
 int /*<<< orphan*/  evict_vmids (struct core_vmid*) ; 
 unsigned int get_existing_vmid_for_ptb (struct core_vmid*,int /*<<< orphan*/ ) ; 
 unsigned int get_next_available_vmid (struct core_vmid*) ; 

uint8_t mod_vmid_get_for_ptb(struct mod_vmid *mod_vmid, uint64_t ptb)
{
	struct core_vmid *core_vmid = MOD_VMID_TO_CORE(mod_vmid);
	unsigned int vmid = 0;

	// Physical address gets vmid 0
	if (ptb == 0)
		return 0;

	vmid = get_existing_vmid_for_ptb(core_vmid, ptb);

	if (vmid == -1) {
		struct dc_virtual_addr_space_config va_config = core_vmid->base_config;

		va_config.page_table_base_addr = ptb;

		if (core_vmid->num_vmids_available == 0)
			evict_vmids(core_vmid);

		vmid = get_next_available_vmid(core_vmid);
		add_ptb_to_table(core_vmid, vmid, ptb);

		dc_setup_vm_context(core_vmid->dc, &va_config, vmid);
	}

	return vmid;
}