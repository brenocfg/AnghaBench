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
typedef  int /*<<< orphan*/  u64 ;
struct kvmppc_slb {int dummy; } ;
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  gva_t ;

/* Variables and functions */
 struct kvmppc_slb* kvmppc_mmu_book3s_64_find_slbe (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_slb_calc_vpn (struct kvmppc_slb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 kvmppc_mmu_book3s_64_ea_to_vp(struct kvm_vcpu *vcpu, gva_t eaddr,
					 bool data)
{
	struct kvmppc_slb *slb;

	slb = kvmppc_mmu_book3s_64_find_slbe(vcpu, eaddr);
	if (!slb)
		return 0;

	return kvmppc_slb_calc_vpn(slb, eaddr);
}