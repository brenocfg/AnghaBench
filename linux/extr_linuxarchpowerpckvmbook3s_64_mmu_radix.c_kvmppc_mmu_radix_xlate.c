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
typedef  int u32 ;
struct kvmppc_pte {int page_size; int eaddr; unsigned long raddr; int may_read; int may_write; int may_execute; } ;
struct TYPE_5__ {int pid; unsigned long amr; unsigned long iamr; } ;
struct kvm_vcpu {TYPE_2__ arch; struct kvm* kvm; } ;
struct TYPE_4__ {int process_table; } ;
struct kvm {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  rpte ;
typedef  int /*<<< orphan*/  prte ;
typedef  int gva_t ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_6__ {unsigned long shift; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int MMU_PAGE_4K ; 
 int MMU_PAGE_COUNT ; 
 int MSR_PR ; 
 int PRTB_MASK ; 
 int PRTS_MASK ; 
 unsigned long RPDB_MASK ; 
 unsigned long RPDS_MASK ; 
 unsigned long RTS1_MASK ; 
 int RTS1_SHIFT ; 
 unsigned long RTS2_MASK ; 
 unsigned long RTS2_SHIFT ; 
 unsigned long _PAGE_EXEC ; 
 unsigned long _PAGE_PRESENT ; 
 unsigned long _PAGE_PRIVILEGED ; 
 unsigned long _PAGE_PTE ; 
 unsigned long _PAGE_READ ; 
 unsigned long _PAGE_WRITE ; 
 unsigned long __be64_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned long be64_to_cpu (int /*<<< orphan*/ ) ; 
 int kvm_read_guest (struct kvm*,unsigned long,int /*<<< orphan*/ *,int) ; 
 int kvmppc_get_msr (struct kvm_vcpu*) ; 
 TYPE_3__* mmu_psize_defs ; 
 unsigned long* p9_supported_radix_bits ; 

int kvmppc_mmu_radix_xlate(struct kvm_vcpu *vcpu, gva_t eaddr,
			   struct kvmppc_pte *gpte, bool data, bool iswrite)
{
	struct kvm *kvm = vcpu->kvm;
	u32 pid;
	int ret, level, ps;
	__be64 prte, rpte;
	unsigned long ptbl;
	unsigned long root, pte, index;
	unsigned long rts, bits, offset;
	unsigned long gpa;
	unsigned long proc_tbl_size;

	/* Work out effective PID */
	switch (eaddr >> 62) {
	case 0:
		pid = vcpu->arch.pid;
		break;
	case 3:
		pid = 0;
		break;
	default:
		return -EINVAL;
	}
	proc_tbl_size = 1 << ((kvm->arch.process_table & PRTS_MASK) + 12);
	if (pid * 16 >= proc_tbl_size)
		return -EINVAL;

	/* Read partition table to find root of tree for effective PID */
	ptbl = (kvm->arch.process_table & PRTB_MASK) + (pid * 16);
	ret = kvm_read_guest(kvm, ptbl, &prte, sizeof(prte));
	if (ret)
		return ret;

	root = be64_to_cpu(prte);
	rts = ((root & RTS1_MASK) >> (RTS1_SHIFT - 3)) |
		((root & RTS2_MASK) >> RTS2_SHIFT);
	bits = root & RPDS_MASK;
	root = root & RPDB_MASK;

	offset = rts + 31;

	/* current implementations only support 52-bit space */
	if (offset != 52)
		return -EINVAL;

	for (level = 3; level >= 0; --level) {
		if (level && bits != p9_supported_radix_bits[level])
			return -EINVAL;
		if (level == 0 && !(bits == 5 || bits == 9))
			return -EINVAL;
		offset -= bits;
		index = (eaddr >> offset) & ((1UL << bits) - 1);
		/* check that low bits of page table base are zero */
		if (root & ((1UL << (bits + 3)) - 1))
			return -EINVAL;
		ret = kvm_read_guest(kvm, root + index * 8,
				     &rpte, sizeof(rpte));
		if (ret)
			return ret;
		pte = __be64_to_cpu(rpte);
		if (!(pte & _PAGE_PRESENT))
			return -ENOENT;
		if (pte & _PAGE_PTE)
			break;
		bits = pte & 0x1f;
		root = pte & 0x0fffffffffffff00ul;
	}
	/* need a leaf at lowest level; 512GB pages not supported */
	if (level < 0 || level == 3)
		return -EINVAL;

	/* offset is now log base 2 of the page size */
	gpa = pte & 0x01fffffffffff000ul;
	if (gpa & ((1ul << offset) - 1))
		return -EINVAL;
	gpa += eaddr & ((1ul << offset) - 1);
	for (ps = MMU_PAGE_4K; ps < MMU_PAGE_COUNT; ++ps)
		if (offset == mmu_psize_defs[ps].shift)
			break;
	gpte->page_size = ps;

	gpte->eaddr = eaddr;
	gpte->raddr = gpa;

	/* Work out permissions */
	gpte->may_read = !!(pte & _PAGE_READ);
	gpte->may_write = !!(pte & _PAGE_WRITE);
	gpte->may_execute = !!(pte & _PAGE_EXEC);
	if (kvmppc_get_msr(vcpu) & MSR_PR) {
		if (pte & _PAGE_PRIVILEGED) {
			gpte->may_read = 0;
			gpte->may_write = 0;
			gpte->may_execute = 0;
		}
	} else {
		if (!(pte & _PAGE_PRIVILEGED)) {
			/* Check AMR/IAMR to see if strict mode is in force */
			if (vcpu->arch.amr & (1ul << 62))
				gpte->may_read = 0;
			if (vcpu->arch.amr & (1ul << 63))
				gpte->may_write = 0;
			if (vcpu->arch.iamr & (1ul << 62))
				gpte->may_execute = 0;
		}
	}

	return 0;
}