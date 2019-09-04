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
struct kvmppc_vcpu_e500 {int dummy; } ;
struct TYPE_2__ {scalar_t__ shared; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct kvmppc_vcpu_e500*) ; 
 int /*<<< orphan*/  kvm_vcpu_cache ; 
 int /*<<< orphan*/  kvm_vcpu_uninit (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_e500_id_table_free (struct kvmppc_vcpu_e500*) ; 
 int /*<<< orphan*/  kvmppc_e500_tlb_uninit (struct kvmppc_vcpu_e500*) ; 
 struct kvmppc_vcpu_e500* to_e500 (struct kvm_vcpu*) ; 

__attribute__((used)) static void kvmppc_core_vcpu_free_e500(struct kvm_vcpu *vcpu)
{
	struct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);

	free_page((unsigned long)vcpu->arch.shared);
	kvmppc_e500_tlb_uninit(vcpu_e500);
	kvmppc_e500_id_table_free(vcpu_e500);
	kvm_vcpu_uninit(vcpu);
	kmem_cache_free(kvm_vcpu_cache, vcpu_e500);
}