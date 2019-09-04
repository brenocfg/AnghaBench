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
struct kvmppc_slb {int valid; scalar_t__ origv; scalar_t__ orige; int /*<<< orphan*/  esid; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int,...) ; 
 struct kvmppc_slb* kvmppc_mmu_book3s_64_find_slbe (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvmppc_mmu_flush_segment (struct kvm_vcpu*,int,int) ; 
 unsigned long long kvmppc_slb_sid_shift (struct kvmppc_slb*) ; 

__attribute__((used)) static void kvmppc_mmu_book3s_64_slbie(struct kvm_vcpu *vcpu, u64 ea)
{
	struct kvmppc_slb *slbe;
	u64 seg_size;

	dprintk("KVM MMU: slbie(0x%llx)\n", ea);

	slbe = kvmppc_mmu_book3s_64_find_slbe(vcpu, ea);

	if (!slbe)
		return;

	dprintk("KVM MMU: slbie(0x%llx, 0x%llx)\n", ea, slbe->esid);

	slbe->valid = false;
	slbe->orige = 0;
	slbe->origv = 0;

	seg_size = 1ull << kvmppc_slb_sid_shift(slbe);
	kvmppc_mmu_flush_segment(vcpu, ea & ~(seg_size - 1), seg_size);
}