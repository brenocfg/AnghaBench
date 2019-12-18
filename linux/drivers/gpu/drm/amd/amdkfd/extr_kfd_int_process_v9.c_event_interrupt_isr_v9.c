#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_5__ {scalar_t__ first_vmid_kfd; scalar_t__ last_vmid_kfd; } ;
struct kfd_dev {int /*<<< orphan*/  kgd; TYPE_4__* kfd2kgd; TYPE_3__* device_info; TYPE_2__* dqm; TYPE_1__ vm_info; } ;
struct TYPE_8__ {scalar_t__ (* get_atc_vmid_pasid_mapping_pasid ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  ih_ring_entry_size; } ;
struct TYPE_6__ {scalar_t__ sched_policy; } ;

/* Variables and functions */
 scalar_t__ KFD_SCHED_POLICY_NO_HWS ; 
 scalar_t__ SOC15_CLIENT_ID_FROM_IH_ENTRY (scalar_t__ const*) ; 
 scalar_t__ SOC15_IH_CLIENTID_UTCL2 ; 
 scalar_t__ SOC15_IH_CLIENTID_VMC ; 
 scalar_t__ SOC15_IH_CLIENTID_VMC1 ; 
 scalar_t__ SOC15_INTSRC_CP_BAD_OPCODE ; 
 scalar_t__ SOC15_INTSRC_CP_END_OF_PIPE ; 
 scalar_t__ SOC15_INTSRC_SDMA_TRAP ; 
 scalar_t__ SOC15_INTSRC_SQ_INTERRUPT_MSG ; 
 scalar_t__ SOC15_PASID_FROM_IH_ENTRY (scalar_t__ const*) ; 
 scalar_t__ SOC15_SOURCE_ID_FROM_IH_ENTRY (scalar_t__ const*) ; 
 scalar_t__ SOC15_VMID_FROM_IH_ENTRY (scalar_t__ const*) ; 
 scalar_t__ WARN_ONCE (int,char*) ; 
 scalar_t__ cpu_to_le32 (scalar_t__ const) ; 
 scalar_t__ const le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__ const,scalar_t__ const,scalar_t__ const,scalar_t__ const,...) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool event_interrupt_isr_v9(struct kfd_dev *dev,
					const uint32_t *ih_ring_entry,
					uint32_t *patched_ihre,
					bool *patched_flag)
{
	uint16_t source_id, client_id, pasid, vmid;
	const uint32_t *data = ih_ring_entry;

	/* Only handle interrupts from KFD VMIDs */
	vmid = SOC15_VMID_FROM_IH_ENTRY(ih_ring_entry);
	if (vmid < dev->vm_info.first_vmid_kfd ||
	    vmid > dev->vm_info.last_vmid_kfd)
		return 0;

	source_id = SOC15_SOURCE_ID_FROM_IH_ENTRY(ih_ring_entry);
	client_id = SOC15_CLIENT_ID_FROM_IH_ENTRY(ih_ring_entry);
	pasid = SOC15_PASID_FROM_IH_ENTRY(ih_ring_entry);

	/* This is a known issue for gfx9. Under non HWS, pasid is not set
	 * in the interrupt payload, so we need to find out the pasid on our
	 * own.
	 */
	if (!pasid && dev->dqm->sched_policy == KFD_SCHED_POLICY_NO_HWS) {
		const uint32_t pasid_mask = 0xffff;

		*patched_flag = true;
		memcpy(patched_ihre, ih_ring_entry,
				dev->device_info->ih_ring_entry_size);

		pasid = dev->kfd2kgd->get_atc_vmid_pasid_mapping_pasid(
				dev->kgd, vmid);

		/* Patch the pasid field */
		patched_ihre[3] = cpu_to_le32((le32_to_cpu(patched_ihre[3])
					& ~pasid_mask) | pasid);
	}

	pr_debug("client id 0x%x, source id %d, vmid %d, pasid 0x%x. raw data:\n",
		 client_id, source_id, vmid, pasid);
	pr_debug("%8X, %8X, %8X, %8X, %8X, %8X, %8X, %8X.\n",
		 data[0], data[1], data[2], data[3],
		 data[4], data[5], data[6], data[7]);

	/* If there is no valid PASID, it's likely a bug */
	if (WARN_ONCE(pasid == 0, "Bug: No PASID in KFD interrupt"))
		return 0;

	/* Interrupt types we care about: various signals and faults.
	 * They will be forwarded to a work queue (see below).
	 */
	return source_id == SOC15_INTSRC_CP_END_OF_PIPE ||
		source_id == SOC15_INTSRC_SDMA_TRAP ||
		source_id == SOC15_INTSRC_SQ_INTERRUPT_MSG ||
		source_id == SOC15_INTSRC_CP_BAD_OPCODE ||
		client_id == SOC15_IH_CLIENTID_VMC ||
		client_id == SOC15_IH_CLIENTID_VMC1 ||
		client_id == SOC15_IH_CLIENTID_UTCL2;
}