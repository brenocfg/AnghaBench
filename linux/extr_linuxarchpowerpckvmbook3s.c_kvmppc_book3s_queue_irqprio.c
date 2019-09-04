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
struct TYPE_4__ {int /*<<< orphan*/  pending_exceptions; } ;
struct TYPE_3__ {int /*<<< orphan*/  queue_intr; } ;
struct kvm_vcpu {TYPE_2__ arch; TYPE_1__ stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvmppc_book3s_vec2irqprio (unsigned int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void kvmppc_book3s_queue_irqprio(struct kvm_vcpu *vcpu, unsigned int vec)
{
	vcpu->stat.queue_intr++;

	set_bit(kvmppc_book3s_vec2irqprio(vec),
		&vcpu->arch.pending_exceptions);
#ifdef EXIT_DEBUG
	printk(KERN_INFO "Queueing interrupt %x\n", vec);
#endif
}