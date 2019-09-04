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
typedef  int u32 ;
struct kvmppc_vcpu_book3s {int sdr1; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
typedef  int hva_t ;
typedef  int gva_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int gfn_to_hva (int /*<<< orphan*/ ,int) ; 
 scalar_t__ kvm_is_error_hva (int) ; 
 int /*<<< orphan*/  kvmppc_get_pc (struct kvm_vcpu*) ; 
 int sr_vsid (int) ; 
 struct kvmppc_vcpu_book3s* to_book3s (struct kvm_vcpu*) ; 

__attribute__((used)) static hva_t kvmppc_mmu_book3s_32_get_pteg(struct kvm_vcpu *vcpu,
				      u32 sre, gva_t eaddr,
				      bool primary)
{
	struct kvmppc_vcpu_book3s *vcpu_book3s = to_book3s(vcpu);
	u32 page, hash, pteg, htabmask;
	hva_t r;

	page = (eaddr & 0x0FFFFFFF) >> 12;
	htabmask = ((vcpu_book3s->sdr1 & 0x1FF) << 16) | 0xFFC0;

	hash = ((sr_vsid(sre) ^ page) << 6);
	if (!primary)
		hash = ~hash;
	hash &= htabmask;

	pteg = (vcpu_book3s->sdr1 & 0xffff0000) | hash;

	dprintk("MMU: pc=0x%lx eaddr=0x%lx sdr1=0x%llx pteg=0x%x vsid=0x%x\n",
		kvmppc_get_pc(vcpu), eaddr, vcpu_book3s->sdr1, pteg,
		sr_vsid(sre));

	r = gfn_to_hva(vcpu->kvm, pteg >> PAGE_SHIFT);
	if (kvm_is_error_hva(r))
		return r;
	return r | (pteg & ~PAGE_MASK);
}