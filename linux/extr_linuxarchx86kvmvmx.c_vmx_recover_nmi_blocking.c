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
typedef  int u8 ;
typedef  int u32 ;
struct vcpu_vmx {int idt_vectoring_info; TYPE_1__* loaded_vmcs; } ;
struct TYPE_2__ {int nmi_known_unmasked; int /*<<< orphan*/  entry_time; int /*<<< orphan*/  vnmi_blocked_time; int /*<<< orphan*/  soft_vnmi_blocked; } ;

/* Variables and functions */
 int DF_VECTOR ; 
 int /*<<< orphan*/  GUEST_INTERRUPTIBILITY_INFO ; 
 int GUEST_INTR_STATE_NMI ; 
 int INTR_INFO_UNBLOCK_NMI ; 
 int INTR_INFO_VALID_MASK ; 
 int INTR_INFO_VECTOR_MASK ; 
 int VECTORING_INFO_VALID_MASK ; 
 int /*<<< orphan*/  VM_EXIT_INTR_INFO ; 
 scalar_t__ enable_vnmi ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int vmcs_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_set_bits (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vmx_recover_nmi_blocking(struct vcpu_vmx *vmx)
{
	u32 exit_intr_info;
	bool unblock_nmi;
	u8 vector;
	bool idtv_info_valid;

	idtv_info_valid = vmx->idt_vectoring_info & VECTORING_INFO_VALID_MASK;

	if (enable_vnmi) {
		if (vmx->loaded_vmcs->nmi_known_unmasked)
			return;
		/*
		 * Can't use vmx->exit_intr_info since we're not sure what
		 * the exit reason is.
		 */
		exit_intr_info = vmcs_read32(VM_EXIT_INTR_INFO);
		unblock_nmi = (exit_intr_info & INTR_INFO_UNBLOCK_NMI) != 0;
		vector = exit_intr_info & INTR_INFO_VECTOR_MASK;
		/*
		 * SDM 3: 27.7.1.2 (September 2008)
		 * Re-set bit "block by NMI" before VM entry if vmexit caused by
		 * a guest IRET fault.
		 * SDM 3: 23.2.2 (September 2008)
		 * Bit 12 is undefined in any of the following cases:
		 *  If the VM exit sets the valid bit in the IDT-vectoring
		 *   information field.
		 *  If the VM exit is due to a double fault.
		 */
		if ((exit_intr_info & INTR_INFO_VALID_MASK) && unblock_nmi &&
		    vector != DF_VECTOR && !idtv_info_valid)
			vmcs_set_bits(GUEST_INTERRUPTIBILITY_INFO,
				      GUEST_INTR_STATE_NMI);
		else
			vmx->loaded_vmcs->nmi_known_unmasked =
				!(vmcs_read32(GUEST_INTERRUPTIBILITY_INFO)
				  & GUEST_INTR_STATE_NMI);
	} else if (unlikely(vmx->loaded_vmcs->soft_vnmi_blocked))
		vmx->loaded_vmcs->vnmi_blocked_time +=
			ktime_to_ns(ktime_sub(ktime_get(),
					      vmx->loaded_vmcs->entry_time));
}