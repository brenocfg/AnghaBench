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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct kfd_vm_fault_info {int page_addr; scalar_t__ prot_write; scalar_t__ prot_read; scalar_t__ prot_valid; scalar_t__ mc_id; scalar_t__ vmid; int /*<<< orphan*/  member_0; } ;
struct kfd_dev {int /*<<< orphan*/  dqm; } ;

/* Variables and functions */
 scalar_t__ SOC15_CLIENT_ID_FROM_IH_ENTRY (int const*) ; 
 int SOC15_CONTEXT_ID0_FROM_IH_ENTRY (int const*) ; 
 scalar_t__ SOC15_IH_CLIENTID_UTCL2 ; 
 scalar_t__ SOC15_IH_CLIENTID_VMC ; 
 scalar_t__ SOC15_IH_CLIENTID_VMC1 ; 
 scalar_t__ SOC15_INTSRC_CP_BAD_OPCODE ; 
 scalar_t__ SOC15_INTSRC_CP_END_OF_PIPE ; 
 scalar_t__ SOC15_INTSRC_SDMA_TRAP ; 
 scalar_t__ SOC15_INTSRC_SQ_INTERRUPT_MSG ; 
 scalar_t__ SOC15_PASID_FROM_IH_ENTRY (int const*) ; 
 scalar_t__ SOC15_RING_ID_FROM_IH_ENTRY (int const*) ; 
 scalar_t__ SOC15_SOURCE_ID_FROM_IH_ENTRY (int const*) ; 
 scalar_t__ SOC15_VMID_FROM_IH_ENTRY (int const*) ; 
 int /*<<< orphan*/  kfd_process_vm_fault (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfd_signal_event_interrupt (scalar_t__,int,int) ; 
 int /*<<< orphan*/  kfd_signal_hw_exception_event (scalar_t__) ; 
 int /*<<< orphan*/  kfd_signal_vm_fault_event (struct kfd_dev*,scalar_t__,struct kfd_vm_fault_info*) ; 

__attribute__((used)) static void event_interrupt_wq_v9(struct kfd_dev *dev,
					const uint32_t *ih_ring_entry)
{
	uint16_t source_id, client_id, pasid, vmid;
	uint32_t context_id;

	source_id = SOC15_SOURCE_ID_FROM_IH_ENTRY(ih_ring_entry);
	client_id = SOC15_CLIENT_ID_FROM_IH_ENTRY(ih_ring_entry);
	pasid = SOC15_PASID_FROM_IH_ENTRY(ih_ring_entry);
	vmid = SOC15_VMID_FROM_IH_ENTRY(ih_ring_entry);
	context_id = SOC15_CONTEXT_ID0_FROM_IH_ENTRY(ih_ring_entry);

	if (source_id == SOC15_INTSRC_CP_END_OF_PIPE)
		kfd_signal_event_interrupt(pasid, context_id, 32);
	else if (source_id == SOC15_INTSRC_SDMA_TRAP)
		kfd_signal_event_interrupt(pasid, context_id & 0xfffffff, 28);
	else if (source_id == SOC15_INTSRC_SQ_INTERRUPT_MSG)
		kfd_signal_event_interrupt(pasid, context_id & 0xffffff, 24);
	else if (source_id == SOC15_INTSRC_CP_BAD_OPCODE)
		kfd_signal_hw_exception_event(pasid);
	else if (client_id == SOC15_IH_CLIENTID_VMC ||
		client_id == SOC15_IH_CLIENTID_VMC1 ||
		 client_id == SOC15_IH_CLIENTID_UTCL2) {
		struct kfd_vm_fault_info info = {0};
		uint16_t ring_id = SOC15_RING_ID_FROM_IH_ENTRY(ih_ring_entry);

		info.vmid = vmid;
		info.mc_id = client_id;
		info.page_addr = ih_ring_entry[4] |
			(uint64_t)(ih_ring_entry[5] & 0xf) << 32;
		info.prot_valid = ring_id & 0x08;
		info.prot_read  = ring_id & 0x10;
		info.prot_write = ring_id & 0x20;

		kfd_process_vm_fault(dev->dqm, pasid);
		kfd_signal_vm_fault_event(dev, pasid, &info);
	}
}