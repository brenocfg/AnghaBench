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
struct kvm_vcpu {int /*<<< orphan*/  cpu; } ;
struct TYPE_3__ {struct kvm_vcpu* kvm_vcpu; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int /*<<< orphan*/  smp_processor_id () ; 

void kvmppc_booke_vcpu_load(struct kvm_vcpu *vcpu, int cpu)
{
	vcpu->cpu = smp_processor_id();
	current->thread.kvm_vcpu = vcpu;
}