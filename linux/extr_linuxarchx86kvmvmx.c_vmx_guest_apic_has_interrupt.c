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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  virtual_apic_page; } ;
struct vcpu_vmx {TYPE_1__ nested; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int APIC_PROCPRI ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  get_vmcs12 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_guest_mode (struct kvm_vcpu*) ; 
 void* kmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_cpu_has_vid (int /*<<< orphan*/ ) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int vmx_get_rvi () ; 

__attribute__((used)) static bool vmx_guest_apic_has_interrupt(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	void *vapic_page;
	u32 vppr;
	int rvi;

	if (WARN_ON_ONCE(!is_guest_mode(vcpu)) ||
		!nested_cpu_has_vid(get_vmcs12(vcpu)) ||
		WARN_ON_ONCE(!vmx->nested.virtual_apic_page))
		return false;

	rvi = vmx_get_rvi();

	vapic_page = kmap(vmx->nested.virtual_apic_page);
	vppr = *((u32 *)(vapic_page + APIC_PROCPRI));
	kunmap(vmx->nested.virtual_apic_page);

	return ((rvi & 0xf0) > (vppr & 0xf0));
}