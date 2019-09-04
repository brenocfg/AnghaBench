#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {unsigned long vm_start; int vm_flags; } ;
struct kvm_vcpu {struct kvm* kvm; } ;
struct kvm_memory_slot {int flags; unsigned long userspace_addr; } ;
struct kvm_hpt_info {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  virt; } ;
struct TYPE_6__ {unsigned long vrma_slb_v; TYPE_1__ hpt; } ;
struct kvm {int /*<<< orphan*/  srcu; TYPE_2__ arch; } ;
struct TYPE_8__ {TYPE_3__* mm; } ;
struct TYPE_7__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 int EINVAL ; 
 int ENOMEM ; 
 int KVM_DEFAULT_HPT_ORDER ; 
 int KVM_MEMSLOT_INVALID ; 
 int /*<<< orphan*/  LPCR_VRMASD ; 
 int LPCR_VRMASD_SH ; 
 int PPC_MIN_HPT_ORDER ; 
 unsigned long SLB_VSID_B_1T ; 
 unsigned long SLB_VSID_SHIFT_1T ; 
 int VM_IO ; 
 unsigned long VRMA_VSID ; 
 unsigned long __ilog2 (unsigned long) ; 
 int /*<<< orphan*/  cpu_has_feature (int /*<<< orphan*/ ) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma (TYPE_3__*,unsigned long) ; 
 struct kvm_memory_slot* gfn_to_memslot (struct kvm*,int /*<<< orphan*/ ) ; 
 int kvmppc_allocate_hpt (struct kvm_hpt_info*,int) ; 
 int /*<<< orphan*/  kvmppc_map_vrma (struct kvm_vcpu*,struct kvm_memory_slot*,unsigned long) ; 
 int /*<<< orphan*/  kvmppc_set_hpt (struct kvm*,struct kvm_hpt_info*) ; 
 int /*<<< orphan*/  kvmppc_update_lpcr (struct kvm*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 unsigned long slb_pgsize_encoding (unsigned long) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 unsigned long vma_kernel_pagesize (struct vm_area_struct*) ; 

__attribute__((used)) static int kvmppc_hv_setup_htab_rma(struct kvm_vcpu *vcpu)
{
	int err = 0;
	struct kvm *kvm = vcpu->kvm;
	unsigned long hva;
	struct kvm_memory_slot *memslot;
	struct vm_area_struct *vma;
	unsigned long lpcr = 0, senc;
	unsigned long psize, porder;
	int srcu_idx;

	/* Allocate hashed page table (if not done already) and reset it */
	if (!kvm->arch.hpt.virt) {
		int order = KVM_DEFAULT_HPT_ORDER;
		struct kvm_hpt_info info;

		err = kvmppc_allocate_hpt(&info, order);
		/* If we get here, it means userspace didn't specify a
		 * size explicitly.  So, try successively smaller
		 * sizes if the default failed. */
		while ((err == -ENOMEM) && --order >= PPC_MIN_HPT_ORDER)
			err  = kvmppc_allocate_hpt(&info, order);

		if (err < 0) {
			pr_err("KVM: Couldn't alloc HPT\n");
			goto out;
		}

		kvmppc_set_hpt(kvm, &info);
	}

	/* Look up the memslot for guest physical address 0 */
	srcu_idx = srcu_read_lock(&kvm->srcu);
	memslot = gfn_to_memslot(kvm, 0);

	/* We must have some memory at 0 by now */
	err = -EINVAL;
	if (!memslot || (memslot->flags & KVM_MEMSLOT_INVALID))
		goto out_srcu;

	/* Look up the VMA for the start of this memory slot */
	hva = memslot->userspace_addr;
	down_read(&current->mm->mmap_sem);
	vma = find_vma(current->mm, hva);
	if (!vma || vma->vm_start > hva || (vma->vm_flags & VM_IO))
		goto up_out;

	psize = vma_kernel_pagesize(vma);

	up_read(&current->mm->mmap_sem);

	/* We can handle 4k, 64k or 16M pages in the VRMA */
	if (psize >= 0x1000000)
		psize = 0x1000000;
	else if (psize >= 0x10000)
		psize = 0x10000;
	else
		psize = 0x1000;
	porder = __ilog2(psize);

	senc = slb_pgsize_encoding(psize);
	kvm->arch.vrma_slb_v = senc | SLB_VSID_B_1T |
		(VRMA_VSID << SLB_VSID_SHIFT_1T);
	/* Create HPTEs in the hash page table for the VRMA */
	kvmppc_map_vrma(vcpu, memslot, porder);

	/* Update VRMASD field in the LPCR */
	if (!cpu_has_feature(CPU_FTR_ARCH_300)) {
		/* the -4 is to account for senc values starting at 0x10 */
		lpcr = senc << (LPCR_VRMASD_SH - 4);
		kvmppc_update_lpcr(kvm, lpcr, LPCR_VRMASD);
	}

	/* Order updates to kvm->arch.lpcr etc. vs. mmu_ready */
	smp_wmb();
	err = 0;
 out_srcu:
	srcu_read_unlock(&kvm->srcu, srcu_idx);
 out:
	return err;

 up_out:
	up_read(&current->mm->mmap_sem);
	goto out_srcu;
}