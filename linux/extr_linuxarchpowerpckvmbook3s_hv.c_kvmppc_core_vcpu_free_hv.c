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
struct TYPE_2__ {int /*<<< orphan*/  vpa_update_lock; int /*<<< orphan*/  vpa; int /*<<< orphan*/  slb_shadow; int /*<<< orphan*/  dtl; } ;
struct kvm_vcpu {TYPE_1__ arch; int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_cache ; 
 int /*<<< orphan*/  kvm_vcpu_uninit (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unpin_vpa (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvmppc_core_vcpu_free_hv(struct kvm_vcpu *vcpu)
{
	spin_lock(&vcpu->arch.vpa_update_lock);
	unpin_vpa(vcpu->kvm, &vcpu->arch.dtl);
	unpin_vpa(vcpu->kvm, &vcpu->arch.slb_shadow);
	unpin_vpa(vcpu->kvm, &vcpu->arch.vpa);
	spin_unlock(&vcpu->arch.vpa_update_lock);
	kvm_vcpu_uninit(vcpu);
	kmem_cache_free(kvm_vcpu_cache, vcpu);
}