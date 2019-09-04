#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_4__ {int** rsvd_bits_mask; } ;
struct TYPE_5__ {TYPE_1__ guest_rsvd_check; } ;
struct TYPE_6__ {int /*<<< orphan*/  regs_dirty; int /*<<< orphan*/  regs_avail; TYPE_2__ mmu; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct kvm_mmu {int* pdptrs; } ;
typedef  int /*<<< orphan*/  pdpte ;
typedef  unsigned long gfn_t ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int PFERR_USER_MASK ; 
 int PFERR_WRITE_MASK ; 
 int PT_PRESENT_MASK ; 
 int /*<<< orphan*/  VCPU_EXREG_PDPTR ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int kvm_read_guest_page_mmu (struct kvm_vcpu*,struct kvm_mmu*,unsigned long,int*,unsigned int,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

int load_pdptrs(struct kvm_vcpu *vcpu, struct kvm_mmu *mmu, unsigned long cr3)
{
	gfn_t pdpt_gfn = cr3 >> PAGE_SHIFT;
	unsigned offset = ((cr3 & (PAGE_SIZE-1)) >> 5) << 2;
	int i;
	int ret;
	u64 pdpte[ARRAY_SIZE(mmu->pdptrs)];

	ret = kvm_read_guest_page_mmu(vcpu, mmu, pdpt_gfn, pdpte,
				      offset * sizeof(u64), sizeof(pdpte),
				      PFERR_USER_MASK|PFERR_WRITE_MASK);
	if (ret < 0) {
		ret = 0;
		goto out;
	}
	for (i = 0; i < ARRAY_SIZE(pdpte); ++i) {
		if ((pdpte[i] & PT_PRESENT_MASK) &&
		    (pdpte[i] &
		     vcpu->arch.mmu.guest_rsvd_check.rsvd_bits_mask[0][2])) {
			ret = 0;
			goto out;
		}
	}
	ret = 1;

	memcpy(mmu->pdptrs, pdpte, sizeof(mmu->pdptrs));
	__set_bit(VCPU_EXREG_PDPTR,
		  (unsigned long *)&vcpu->arch.regs_avail);
	__set_bit(VCPU_EXREG_PDPTR,
		  (unsigned long *)&vcpu->arch.regs_dirty);
out:

	return ret;
}