#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int cr14; } ;
struct TYPE_16__ {TYPE_6__ mchk; } ;
struct TYPE_17__ {TYPE_7__ irq; } ;
struct TYPE_18__ {TYPE_8__ local_int; TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_9__ arch; TYPE_5__* kvm; } ;
struct TYPE_11__ {int cr14; } ;
struct TYPE_12__ {TYPE_2__ mchk; } ;
struct TYPE_13__ {TYPE_3__ float_int; } ;
struct TYPE_14__ {TYPE_4__ arch; } ;
struct TYPE_10__ {int* gcr; } ;

/* Variables and functions */
 int CR0_CLOCK_COMPARATOR_SUBMASK ; 
 int CR0_CPU_TIMER_SUBMASK ; 
 int CR0_EMERGENCY_SIGNAL_SUBMASK ; 
 int CR0_EXTERNAL_CALL_SUBMASK ; 
 int CR0_SERVICE_SIGNAL_SUBMASK ; 
 int /*<<< orphan*/  IRQ_PEND_EXT_CLOCK_COMP ; 
 int /*<<< orphan*/  IRQ_PEND_EXT_CPU_TIMER ; 
 int /*<<< orphan*/  IRQ_PEND_EXT_EMERGENCY ; 
 int /*<<< orphan*/  IRQ_PEND_EXT_EXTERNAL ; 
 unsigned long IRQ_PEND_EXT_MASK ; 
 int /*<<< orphan*/  IRQ_PEND_EXT_SERVICE ; 
 unsigned long IRQ_PEND_IO_MASK ; 
 unsigned long IRQ_PEND_MCHK_MASK ; 
 int /*<<< orphan*/  IRQ_PEND_MCHK_REP ; 
 int /*<<< orphan*/  IRQ_PEND_SIGP_STOP ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 unsigned long disable_iscs (struct kvm_vcpu*,unsigned long) ; 
 unsigned long pending_irqs (struct kvm_vcpu*) ; 
 scalar_t__ psw_extint_disabled (struct kvm_vcpu*) ; 
 scalar_t__ psw_ioint_disabled (struct kvm_vcpu*) ; 
 scalar_t__ psw_mchk_disabled (struct kvm_vcpu*) ; 

__attribute__((used)) static unsigned long deliverable_irqs(struct kvm_vcpu *vcpu)
{
	unsigned long active_mask;

	active_mask = pending_irqs(vcpu);
	if (!active_mask)
		return 0;

	if (psw_extint_disabled(vcpu))
		active_mask &= ~IRQ_PEND_EXT_MASK;
	if (psw_ioint_disabled(vcpu))
		active_mask &= ~IRQ_PEND_IO_MASK;
	else
		active_mask = disable_iscs(vcpu, active_mask);
	if (!(vcpu->arch.sie_block->gcr[0] & CR0_EXTERNAL_CALL_SUBMASK))
		__clear_bit(IRQ_PEND_EXT_EXTERNAL, &active_mask);
	if (!(vcpu->arch.sie_block->gcr[0] & CR0_EMERGENCY_SIGNAL_SUBMASK))
		__clear_bit(IRQ_PEND_EXT_EMERGENCY, &active_mask);
	if (!(vcpu->arch.sie_block->gcr[0] & CR0_CLOCK_COMPARATOR_SUBMASK))
		__clear_bit(IRQ_PEND_EXT_CLOCK_COMP, &active_mask);
	if (!(vcpu->arch.sie_block->gcr[0] & CR0_CPU_TIMER_SUBMASK))
		__clear_bit(IRQ_PEND_EXT_CPU_TIMER, &active_mask);
	if (!(vcpu->arch.sie_block->gcr[0] & CR0_SERVICE_SIGNAL_SUBMASK))
		__clear_bit(IRQ_PEND_EXT_SERVICE, &active_mask);
	if (psw_mchk_disabled(vcpu))
		active_mask &= ~IRQ_PEND_MCHK_MASK;
	/*
	 * Check both floating and local interrupt's cr14 because
	 * bit IRQ_PEND_MCHK_REP could be set in both cases.
	 */
	if (!(vcpu->arch.sie_block->gcr[14] &
	   (vcpu->kvm->arch.float_int.mchk.cr14 |
	   vcpu->arch.local_int.irq.mchk.cr14)))
		__clear_bit(IRQ_PEND_MCHK_REP, &active_mask);

	/*
	 * STOP irqs will never be actively delivered. They are triggered via
	 * intercept requests and cleared when the stop intercept is performed.
	 */
	__clear_bit(IRQ_PEND_SIGP_STOP, &active_mask);

	return active_mask;
}