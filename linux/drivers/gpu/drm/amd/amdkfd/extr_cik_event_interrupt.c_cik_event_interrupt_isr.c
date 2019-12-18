#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {unsigned int first_vmid_kfd; unsigned int last_vmid_kfd; } ;
struct kfd_dev {TYPE_2__ vm_info; int /*<<< orphan*/  kgd; TYPE_1__* device_info; struct kfd2kgd_calls* kfd2kgd; } ;
struct kfd2kgd_calls {unsigned int (* read_vmid_from_vmfault_reg ) (int /*<<< orphan*/ ) ;unsigned int (* get_atc_vmid_pasid_mapping_pasid ) (int /*<<< orphan*/ ,unsigned int) ;} ;
struct cik_ih_ring_entry {scalar_t__ source_id; int ring_id; } ;
struct TYPE_3__ {scalar_t__ asic_family; } ;

/* Variables and functions */
 scalar_t__ CHIP_HAWAII ; 
 scalar_t__ CIK_INTSRC_CP_BAD_OPCODE ; 
 scalar_t__ CIK_INTSRC_CP_END_OF_PIPE ; 
 scalar_t__ CIK_INTSRC_GFX_MEM_PROT_FAULT ; 
 scalar_t__ CIK_INTSRC_GFX_PAGE_INV_FAULT ; 
 scalar_t__ CIK_INTSRC_SDMA_TRAP ; 
 scalar_t__ CIK_INTSRC_SQ_INTERRUPT_MSG ; 
 scalar_t__ WARN_ONCE (int,char*) ; 
 unsigned int stub1 (int /*<<< orphan*/ ) ; 
 unsigned int stub2 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static bool cik_event_interrupt_isr(struct kfd_dev *dev,
					const uint32_t *ih_ring_entry,
					uint32_t *patched_ihre,
					bool *patched_flag)
{
	const struct cik_ih_ring_entry *ihre =
			(const struct cik_ih_ring_entry *)ih_ring_entry;
	const struct kfd2kgd_calls *f2g = dev->kfd2kgd;
	unsigned int vmid, pasid;

	/* This workaround is due to HW/FW limitation on Hawaii that
	 * VMID and PASID are not written into ih_ring_entry
	 */
	if ((ihre->source_id == CIK_INTSRC_GFX_PAGE_INV_FAULT ||
		ihre->source_id == CIK_INTSRC_GFX_MEM_PROT_FAULT) &&
		dev->device_info->asic_family == CHIP_HAWAII) {
		struct cik_ih_ring_entry *tmp_ihre =
			(struct cik_ih_ring_entry *)patched_ihre;

		*patched_flag = true;
		*tmp_ihre = *ihre;

		vmid = f2g->read_vmid_from_vmfault_reg(dev->kgd);
		pasid = f2g->get_atc_vmid_pasid_mapping_pasid(dev->kgd, vmid);

		tmp_ihre->ring_id &= 0x000000ff;
		tmp_ihre->ring_id |= vmid << 8;
		tmp_ihre->ring_id |= pasid << 16;

		return (pasid != 0) &&
			vmid >= dev->vm_info.first_vmid_kfd &&
			vmid <= dev->vm_info.last_vmid_kfd;
	}

	/* Only handle interrupts from KFD VMIDs */
	vmid  = (ihre->ring_id & 0x0000ff00) >> 8;
	if (vmid < dev->vm_info.first_vmid_kfd ||
	    vmid > dev->vm_info.last_vmid_kfd)
		return 0;

	/* If there is no valid PASID, it's likely a firmware bug */
	pasid = (ihre->ring_id & 0xffff0000) >> 16;
	if (WARN_ONCE(pasid == 0, "FW bug: No PASID in KFD interrupt"))
		return 0;

	/* Interrupt types we care about: various signals and faults.
	 * They will be forwarded to a work queue (see below).
	 */
	return ihre->source_id == CIK_INTSRC_CP_END_OF_PIPE ||
		ihre->source_id == CIK_INTSRC_SDMA_TRAP ||
		ihre->source_id == CIK_INTSRC_SQ_INTERRUPT_MSG ||
		ihre->source_id == CIK_INTSRC_CP_BAD_OPCODE ||
		ihre->source_id == CIK_INTSRC_GFX_PAGE_INV_FAULT ||
		ihre->source_id == CIK_INTSRC_GFX_MEM_PROT_FAULT;
}