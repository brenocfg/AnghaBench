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
typedef  void* ulong ;
struct TYPE_2__ {void* queued_esr; void* queued_dear; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOKE_IRQPRIO_DTLB_MISS ; 
 int /*<<< orphan*/  kvmppc_booke_queue_irqprio (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

void kvmppc_core_queue_dtlb_miss(struct kvm_vcpu *vcpu,
				 ulong dear_flags, ulong esr_flags)
{
	vcpu->arch.queued_dear = dear_flags;
	vcpu->arch.queued_esr = esr_flags;
	kvmppc_booke_queue_irqprio(vcpu, BOOKE_IRQPRIO_DTLB_MISS);
}