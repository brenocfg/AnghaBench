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
typedef  unsigned long long u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct kvmppc_vcpu_book3s {int sdr1; } ;
struct kvmppc_slb {int /*<<< orphan*/  vsid; scalar_t__ tb; } ;
struct TYPE_2__ {scalar_t__ papr_enabled; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_1__ arch; } ;
typedef  unsigned long long hva_t ;
typedef  int /*<<< orphan*/  gva_t ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_SEGSIZE_1T ; 
 int /*<<< orphan*/  MMU_SEGSIZE_256M ; 
 unsigned long long PAGE_MASK ; 
 unsigned long long PAGE_SHIFT ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int,unsigned long long,int /*<<< orphan*/ ) ; 
 unsigned long long gfn_to_hva (int /*<<< orphan*/ ,unsigned long long) ; 
 unsigned long long hpt_hash (unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_is_error_hva (unsigned long long) ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_64_get_pagesize (struct kvmppc_slb*) ; 
 unsigned long long kvmppc_slb_calc_vpn (struct kvmppc_slb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page ; 
 struct kvmppc_vcpu_book3s* to_book3s (struct kvm_vcpu*) ; 

__attribute__((used)) static hva_t kvmppc_mmu_book3s_64_get_pteg(struct kvm_vcpu *vcpu,
				struct kvmppc_slb *slbe, gva_t eaddr,
				bool second)
{
	struct kvmppc_vcpu_book3s *vcpu_book3s = to_book3s(vcpu);
	u64 hash, pteg, htabsize;
	u32 ssize;
	hva_t r;
	u64 vpn;

	htabsize = ((1 << ((vcpu_book3s->sdr1 & 0x1f) + 11)) - 1);

	vpn = kvmppc_slb_calc_vpn(slbe, eaddr);
	ssize = slbe->tb ? MMU_SEGSIZE_1T : MMU_SEGSIZE_256M;
	hash = hpt_hash(vpn, kvmppc_mmu_book3s_64_get_pagesize(slbe), ssize);
	if (second)
		hash = ~hash;
	hash &= ((1ULL << 39ULL) - 1ULL);
	hash &= htabsize;
	hash <<= 7ULL;

	pteg = vcpu_book3s->sdr1 & 0xfffffffffffc0000ULL;
	pteg |= hash;

	dprintk("MMU: page=0x%x sdr1=0x%llx pteg=0x%llx vsid=0x%llx\n",
		page, vcpu_book3s->sdr1, pteg, slbe->vsid);

	/* When running a PAPR guest, SDR1 contains a HVA address instead
           of a GPA */
	if (vcpu->arch.papr_enabled)
		r = pteg;
	else
		r = gfn_to_hva(vcpu->kvm, pteg >> PAGE_SHIFT);

	if (kvm_is_error_hva(r))
		return r;
	return r | (pteg & ~PAGE_MASK);
}