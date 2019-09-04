#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
struct kvmppc_vcpu_book3s {int* context_id; int proto_vsid_max; int proto_vsid_first; int proto_vsid_next; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int ESID_BITS ; 
 int hash__alloc_context_id () ; 
 int /*<<< orphan*/  kvmppc_mmu_hpte_init (struct kvm_vcpu*) ; 
 struct kvmppc_vcpu_book3s* to_book3s (struct kvm_vcpu*) ; 

int kvmppc_mmu_init(struct kvm_vcpu *vcpu)
{
	struct kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	int err;

	err = hash__alloc_context_id();
	if (err < 0)
		return -1;
	vcpu3s->context_id[0] = err;

	vcpu3s->proto_vsid_max = ((u64)(vcpu3s->context_id[0] + 1)
				  << ESID_BITS) - 1;
	vcpu3s->proto_vsid_first = (u64)vcpu3s->context_id[0] << ESID_BITS;
	vcpu3s->proto_vsid_next = vcpu3s->proto_vsid_first;

	kvmppc_mmu_hpte_init(vcpu);

	return 0;
}