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
struct TYPE_3__ {void* wbinvd_dirty_mask; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* vcpu_free ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free_cpumask_var (void*) ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  kvmclock_reset (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*) ; 

void kvm_arch_vcpu_free(struct kvm_vcpu *vcpu)
{
	void *wbinvd_dirty_mask = vcpu->arch.wbinvd_dirty_mask;

	kvmclock_reset(vcpu);

	kvm_x86_ops->vcpu_free(vcpu);
	free_cpumask_var(wbinvd_dirty_mask);
}