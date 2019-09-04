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
typedef  scalar_t__ u64 ;
struct kvmppc_slb {scalar_t__ esid; scalar_t__ vsid; scalar_t__ tb; scalar_t__ large; scalar_t__ valid; } ;
struct TYPE_2__ {int slb_nr; struct kvmppc_slb* slb; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  gva_t ;

/* Variables and functions */
 scalar_t__ GET_ESID (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_ESID_1T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int,char,char,...) ; 

__attribute__((used)) static struct kvmppc_slb *kvmppc_mmu_book3s_64_find_slbe(
				struct kvm_vcpu *vcpu,
				gva_t eaddr)
{
	int i;
	u64 esid = GET_ESID(eaddr);
	u64 esid_1t = GET_ESID_1T(eaddr);

	for (i = 0; i < vcpu->arch.slb_nr; i++) {
		u64 cmp_esid = esid;

		if (!vcpu->arch.slb[i].valid)
			continue;

		if (vcpu->arch.slb[i].tb)
			cmp_esid = esid_1t;

		if (vcpu->arch.slb[i].esid == cmp_esid)
			return &vcpu->arch.slb[i];
	}

	dprintk("KVM: No SLB entry found for 0x%lx [%llx | %llx]\n",
		eaddr, esid, esid_1t);
	for (i = 0; i < vcpu->arch.slb_nr; i++) {
	    if (vcpu->arch.slb[i].vsid)
		dprintk("  %d: %c%c%c %llx %llx\n", i,
			vcpu->arch.slb[i].valid ? 'v' : ' ',
			vcpu->arch.slb[i].large ? 'l' : ' ',
			vcpu->arch.slb[i].tb    ? 't' : ' ',
			vcpu->arch.slb[i].esid,
			vcpu->arch.slb[i].vsid);
	}

	return NULL;
}