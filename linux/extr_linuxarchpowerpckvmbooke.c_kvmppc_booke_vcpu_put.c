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
struct kvm_vcpu {int cpu; } ;
struct TYPE_3__ {int /*<<< orphan*/ * kvm_vcpu; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int /*<<< orphan*/  kvmppc_clear_dbsr () ; 

void kvmppc_booke_vcpu_put(struct kvm_vcpu *vcpu)
{
	current->thread.kvm_vcpu = NULL;
	vcpu->cpu = -1;

	/* Clear pending debug event in DBSR */
	kvmppc_clear_dbsr();
}