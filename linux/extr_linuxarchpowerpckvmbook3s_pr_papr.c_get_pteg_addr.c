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
struct kvmppc_vcpu_book3s {int sdr1; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 struct kvmppc_vcpu_book3s* to_book3s (struct kvm_vcpu*) ; 

__attribute__((used)) static unsigned long get_pteg_addr(struct kvm_vcpu *vcpu, long pte_index)
{
	struct kvmppc_vcpu_book3s *vcpu_book3s = to_book3s(vcpu);
	unsigned long pteg_addr;

	pte_index <<= 4;
	pte_index &= ((1 << ((vcpu_book3s->sdr1 & 0x1f) + 11)) - 1) << 7 | 0x70;
	pteg_addr = vcpu_book3s->sdr1 & 0xfffffffffffc0000ULL;
	pteg_addr |= pte_index;

	return pteg_addr;
}