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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_3__ {int pi_pending; int /*<<< orphan*/  virtual_apic_page; TYPE_2__* pi_desc; } ;
struct vcpu_vmx {TYPE_1__ nested; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_4__ {scalar_t__ pir; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUEST_INTR_STATUS ; 
 int /*<<< orphan*/  __kvm_apic_update_irr (scalar_t__,void*,int*) ; 
 int find_last_bit (unsigned long*,int) ; 
 void* kmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_mark_vmcs12_pages_dirty (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  pi_test_and_clear_on (TYPE_2__*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int vmcs_read16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write16 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vmx_complete_nested_posted_interrupt(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	int max_irr;
	void *vapic_page;
	u16 status;

	if (!vmx->nested.pi_desc || !vmx->nested.pi_pending)
		return;

	vmx->nested.pi_pending = false;
	if (!pi_test_and_clear_on(vmx->nested.pi_desc))
		return;

	max_irr = find_last_bit((unsigned long *)vmx->nested.pi_desc->pir, 256);
	if (max_irr != 256) {
		vapic_page = kmap(vmx->nested.virtual_apic_page);
		__kvm_apic_update_irr(vmx->nested.pi_desc->pir,
			vapic_page, &max_irr);
		kunmap(vmx->nested.virtual_apic_page);

		status = vmcs_read16(GUEST_INTR_STATUS);
		if ((u8)max_irr > ((u8)status & 0xff)) {
			status &= ~0xff;
			status |= (u8)max_irr;
			vmcs_write16(GUEST_INTR_STATUS, status);
		}
	}

	nested_mark_vmcs12_pages_dirty(vcpu);
}