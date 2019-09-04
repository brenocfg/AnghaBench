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
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  apic; } ;
struct kvm_vcpu {int vcpu_id; TYPE_2__* kvm; TYPE_3__ arch; } ;
struct kvm_lapic_state {scalar_t__ regs; } ;
struct TYPE_4__ {scalar_t__ x2apic_format; } ;
struct TYPE_5__ {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ APIC_ID ; 
 scalar_t__ APIC_LDR ; 
 int EINVAL ; 
 scalar_t__ apic_x2apic_mode (int /*<<< orphan*/ ) ; 
 int kvm_apic_calc_x2apic_ldr (int) ; 

__attribute__((used)) static int kvm_apic_state_fixup(struct kvm_vcpu *vcpu,
		struct kvm_lapic_state *s, bool set)
{
	if (apic_x2apic_mode(vcpu->arch.apic)) {
		u32 *id = (u32 *)(s->regs + APIC_ID);
		u32 *ldr = (u32 *)(s->regs + APIC_LDR);

		if (vcpu->kvm->arch.x2apic_format) {
			if (*id != vcpu->vcpu_id)
				return -EINVAL;
		} else {
			if (set)
				*id >>= 24;
			else
				*id <<= 24;
		}

		/* In x2APIC mode, the LDR is fixed and based on the id */
		if (set)
			*ldr = kvm_apic_calc_x2apic_ldr(*id);
	}

	return 0;
}