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
struct TYPE_4__ {unsigned long KVM_ARM_SVC_spsr; unsigned long KVM_ARM_ABT_spsr; unsigned long KVM_ARM_UND_spsr; unsigned long KVM_ARM_IRQ_spsr; unsigned long KVM_ARM_FIQ_spsr; } ;
struct TYPE_5__ {TYPE_1__ gp_regs; } ;
struct TYPE_6__ {TYPE_2__ ctxt; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;

/* Variables and functions */
#define  ABT_MODE 132 
 int /*<<< orphan*/  BUG () ; 
#define  FIQ_MODE 131 
#define  IRQ_MODE 130 
 unsigned long MODE_MASK ; 
#define  SVC_MODE 129 
#define  UND_MODE 128 
 unsigned long* vcpu_cpsr (struct kvm_vcpu*) ; 

unsigned long *__vcpu_spsr(struct kvm_vcpu *vcpu)
{
	unsigned long mode = *vcpu_cpsr(vcpu) & MODE_MASK;
	switch (mode) {
	case SVC_MODE:
		return &vcpu->arch.ctxt.gp_regs.KVM_ARM_SVC_spsr;
	case ABT_MODE:
		return &vcpu->arch.ctxt.gp_regs.KVM_ARM_ABT_spsr;
	case UND_MODE:
		return &vcpu->arch.ctxt.gp_regs.KVM_ARM_UND_spsr;
	case IRQ_MODE:
		return &vcpu->arch.ctxt.gp_regs.KVM_ARM_IRQ_spsr;
	case FIQ_MODE:
		return &vcpu->arch.ctxt.gp_regs.KVM_ARM_FIQ_spsr;
	default:
		BUG();
	}
}