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
struct TYPE_2__ {int /*<<< orphan*/  cop0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int C_IRQ5 ; 
 int C_TI ; 
 int /*<<< orphan*/  MIPS_EXC_INT_TIMER ; 
 int /*<<< orphan*/  kvm_mips_queue_irq (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_c0_guest_cause (int /*<<< orphan*/ ,int) ; 

void kvm_mips_queue_timer_int_cb(struct kvm_vcpu *vcpu)
{
	/*
	 * Cause bits to reflect the pending timer interrupt,
	 * the EXC code will be set when we are actually
	 * delivering the interrupt:
	 */
	kvm_set_c0_guest_cause(vcpu->arch.cop0, (C_IRQ5 | C_TI));

	/* Queue up an INT exception for the core */
	kvm_mips_queue_irq(vcpu, MIPS_EXC_INT_TIMER);

}