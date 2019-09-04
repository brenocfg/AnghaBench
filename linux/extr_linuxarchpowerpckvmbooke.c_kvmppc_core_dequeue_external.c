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
struct TYPE_2__ {int /*<<< orphan*/  pending_exceptions; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOKE_IRQPRIO_EXTERNAL ; 
 int /*<<< orphan*/  BOOKE_IRQPRIO_EXTERNAL_LEVEL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void kvmppc_core_dequeue_external(struct kvm_vcpu *vcpu)
{
	clear_bit(BOOKE_IRQPRIO_EXTERNAL, &vcpu->arch.pending_exceptions);
	clear_bit(BOOKE_IRQPRIO_EXTERNAL_LEVEL, &vcpu->arch.pending_exceptions);
}