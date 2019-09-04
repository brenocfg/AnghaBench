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
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * context_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  __destroy_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_mmu_hpte_destroy (struct kvm_vcpu*) ; 
 TYPE_1__* to_book3s (struct kvm_vcpu*) ; 

void kvmppc_mmu_destroy_pr(struct kvm_vcpu *vcpu)
{
	kvmppc_mmu_hpte_destroy(vcpu);
	__destroy_context(to_book3s(vcpu)->context_id[0]);
}