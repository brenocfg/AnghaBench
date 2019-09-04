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
struct TYPE_2__ {int tcr; int tsr; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int TCR_DIE ; 
 int TCR_WIE ; 
 int TSR_DIS ; 
 int TSR_WIS ; 
 int /*<<< orphan*/  kvmppc_core_dequeue_dec (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_core_dequeue_watchdog (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_core_queue_dec (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_core_queue_watchdog (struct kvm_vcpu*) ; 

__attribute__((used)) static void update_timer_ints(struct kvm_vcpu *vcpu)
{
	if ((vcpu->arch.tcr & TCR_DIE) && (vcpu->arch.tsr & TSR_DIS))
		kvmppc_core_queue_dec(vcpu);
	else
		kvmppc_core_dequeue_dec(vcpu);

	if ((vcpu->arch.tcr & TCR_WIE) && (vcpu->arch.tsr & TSR_WIS))
		kvmppc_core_queue_watchdog(vcpu);
	else
		kvmppc_core_dequeue_watchdog(vcpu);
}