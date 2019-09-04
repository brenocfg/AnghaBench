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
typedef  size_t u64 ;
struct kvmppc_slb {size_t origv; } ;
struct TYPE_2__ {size_t slb_nr; struct kvmppc_slb* slb; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */

__attribute__((used)) static u64 kvmppc_mmu_book3s_64_slbmfev(struct kvm_vcpu *vcpu, u64 slb_nr)
{
	struct kvmppc_slb *slbe;

	if (slb_nr > vcpu->arch.slb_nr)
		return 0;

	slbe = &vcpu->arch.slb[slb_nr];

	return slbe->origv;
}