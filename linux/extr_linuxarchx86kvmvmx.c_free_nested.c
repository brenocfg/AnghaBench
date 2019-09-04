#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int vmxon; } ;
struct TYPE_6__ {int vmxon; int posted_intr_nv; unsigned long long current_vmptr; int /*<<< orphan*/  vmcs02; int /*<<< orphan*/ * pi_desc; int /*<<< orphan*/ * pi_desc_page; int /*<<< orphan*/ * virtual_apic_page; int /*<<< orphan*/ * apic_access_page; int /*<<< orphan*/  cached_shadow_vmcs12; int /*<<< orphan*/  cached_vmcs12; int /*<<< orphan*/  vpid02; TYPE_1__ smm; int /*<<< orphan*/  preemption_timer; } ;
struct TYPE_5__ {int /*<<< orphan*/ * shadow_vmcs; } ;
struct vcpu_vmx {TYPE_3__ nested; TYPE_2__ vmcs01; } ;

/* Variables and functions */
 scalar_t__ enable_shadow_vmcs ; 
 int /*<<< orphan*/  free_loaded_vmcs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_vmcs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_vpid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_release_page_dirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmcs_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmx_disable_shadow_vmcs (struct vcpu_vmx*) ; 

__attribute__((used)) static void free_nested(struct vcpu_vmx *vmx)
{
	if (!vmx->nested.vmxon && !vmx->nested.smm.vmxon)
		return;

	hrtimer_cancel(&vmx->nested.preemption_timer);
	vmx->nested.vmxon = false;
	vmx->nested.smm.vmxon = false;
	free_vpid(vmx->nested.vpid02);
	vmx->nested.posted_intr_nv = -1;
	vmx->nested.current_vmptr = -1ull;
	if (enable_shadow_vmcs) {
		vmx_disable_shadow_vmcs(vmx);
		vmcs_clear(vmx->vmcs01.shadow_vmcs);
		free_vmcs(vmx->vmcs01.shadow_vmcs);
		vmx->vmcs01.shadow_vmcs = NULL;
	}
	kfree(vmx->nested.cached_vmcs12);
	kfree(vmx->nested.cached_shadow_vmcs12);
	/* Unpin physical memory we referred to in the vmcs02 */
	if (vmx->nested.apic_access_page) {
		kvm_release_page_dirty(vmx->nested.apic_access_page);
		vmx->nested.apic_access_page = NULL;
	}
	if (vmx->nested.virtual_apic_page) {
		kvm_release_page_dirty(vmx->nested.virtual_apic_page);
		vmx->nested.virtual_apic_page = NULL;
	}
	if (vmx->nested.pi_desc_page) {
		kunmap(vmx->nested.pi_desc_page);
		kvm_release_page_dirty(vmx->nested.pi_desc_page);
		vmx->nested.pi_desc_page = NULL;
		vmx->nested.pi_desc = NULL;
	}

	free_loaded_vmcs(&vmx->nested.vmcs02);
}