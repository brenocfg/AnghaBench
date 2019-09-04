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
struct TYPE_2__ {unsigned long long current_vmptr; int sync_shadow_vmcs; int posted_intr_nv; int /*<<< orphan*/  cached_vmcs12; } ;
struct vcpu_vmx {TYPE_1__ nested; int /*<<< orphan*/  vcpu; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  VMCS12_SIZE ; 
 int /*<<< orphan*/  copy_shadow_to_vmcs12 (struct vcpu_vmx*) ; 
 scalar_t__ enable_shadow_vmcs ; 
 int /*<<< orphan*/  kvm_vcpu_write_guest_page (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_disable_shadow_vmcs (struct vcpu_vmx*) ; 

__attribute__((used)) static inline void nested_release_vmcs12(struct vcpu_vmx *vmx)
{
	if (vmx->nested.current_vmptr == -1ull)
		return;

	if (enable_shadow_vmcs) {
		/* copy to memory all shadowed fields in case
		   they were modified */
		copy_shadow_to_vmcs12(vmx);
		vmx->nested.sync_shadow_vmcs = false;
		vmx_disable_shadow_vmcs(vmx);
	}
	vmx->nested.posted_intr_nv = -1;

	/* Flush VMCS12 to guest memory */
	kvm_vcpu_write_guest_page(&vmx->vcpu,
				  vmx->nested.current_vmptr >> PAGE_SHIFT,
				  vmx->nested.cached_vmcs12, 0, VMCS12_SIZE);

	vmx->nested.current_vmptr = -1ull;
}