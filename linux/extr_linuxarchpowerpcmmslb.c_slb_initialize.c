#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long vmalloc_sllp; int kstack; int /*<<< orphan*/  stab_rr; } ;
struct TYPE_3__ {unsigned long sllp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KSTACK_INDEX ; 
 int /*<<< orphan*/  LINEAR_INDEX ; 
 int PAGE_OFFSET ; 
 int /*<<< orphan*/  SLB_NUM_BOLTED ; 
 unsigned long SLB_VSID_KERNEL ; 
 int /*<<< orphan*/  VMALLOC_INDEX ; 
 int VMALLOC_START ; 
 scalar_t__ boot_cpuid ; 
 int /*<<< orphan*/  create_shadowed_slbe (int,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_2__* get_paca () ; 
 size_t mmu_io_psize ; 
 int /*<<< orphan*/  mmu_kernel_ssize ; 
 size_t mmu_linear_psize ; 
 TYPE_1__* mmu_psize_defs ; 
 unsigned long mmu_slb_size ; 
 size_t mmu_vmalloc_psize ; 
 int /*<<< orphan*/  patch_slb_encoding (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pr_devel (char*,unsigned long) ; 
 scalar_t__ raw_smp_processor_id () ; 
 int /*<<< orphan*/  slb_compare_rr_to_size ; 
 int slb_esid_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slb_miss_kernel_load_io ; 
 int /*<<< orphan*/  slb_miss_kernel_load_linear ; 
 int /*<<< orphan*/  slb_shadow_clear (int /*<<< orphan*/ ) ; 

void slb_initialize(void)
{
	unsigned long linear_llp, vmalloc_llp, io_llp;
	unsigned long lflags, vflags;
	static int slb_encoding_inited;
#ifdef CONFIG_SPARSEMEM_VMEMMAP
	unsigned long vmemmap_llp;
#endif

	/* Prepare our SLB miss handler based on our page size */
	linear_llp = mmu_psize_defs[mmu_linear_psize].sllp;
	io_llp = mmu_psize_defs[mmu_io_psize].sllp;
	vmalloc_llp = mmu_psize_defs[mmu_vmalloc_psize].sllp;
	get_paca()->vmalloc_sllp = SLB_VSID_KERNEL | vmalloc_llp;
#ifdef CONFIG_SPARSEMEM_VMEMMAP
	vmemmap_llp = mmu_psize_defs[mmu_vmemmap_psize].sllp;
#endif
	if (!slb_encoding_inited) {
		slb_encoding_inited = 1;
		patch_slb_encoding(slb_miss_kernel_load_linear,
				   SLB_VSID_KERNEL | linear_llp);
		patch_slb_encoding(slb_miss_kernel_load_io,
				   SLB_VSID_KERNEL | io_llp);
		patch_slb_encoding(slb_compare_rr_to_size,
				   mmu_slb_size);

		pr_devel("SLB: linear  LLP = %04lx\n", linear_llp);
		pr_devel("SLB: io      LLP = %04lx\n", io_llp);

#ifdef CONFIG_SPARSEMEM_VMEMMAP
		patch_slb_encoding(slb_miss_kernel_load_vmemmap,
				   SLB_VSID_KERNEL | vmemmap_llp);
		pr_devel("SLB: vmemmap LLP = %04lx\n", vmemmap_llp);
#endif
	}

	get_paca()->stab_rr = SLB_NUM_BOLTED;

	lflags = SLB_VSID_KERNEL | linear_llp;
	vflags = SLB_VSID_KERNEL | vmalloc_llp;

	/* Invalidate the entire SLB (even entry 0) & all the ERATS */
	asm volatile("isync":::"memory");
	asm volatile("slbmte  %0,%0"::"r" (0) : "memory");
	asm volatile("isync; slbia; isync":::"memory");
	create_shadowed_slbe(PAGE_OFFSET, mmu_kernel_ssize, lflags, LINEAR_INDEX);
	create_shadowed_slbe(VMALLOC_START, mmu_kernel_ssize, vflags, VMALLOC_INDEX);

	/* For the boot cpu, we're running on the stack in init_thread_union,
	 * which is in the first segment of the linear mapping, and also
	 * get_paca()->kstack hasn't been initialized yet.
	 * For secondary cpus, we need to bolt the kernel stack entry now.
	 */
	slb_shadow_clear(KSTACK_INDEX);
	if (raw_smp_processor_id() != boot_cpuid &&
	    (get_paca()->kstack & slb_esid_mask(mmu_kernel_ssize)) > PAGE_OFFSET)
		create_shadowed_slbe(get_paca()->kstack,
				     mmu_kernel_ssize, lflags, KSTACK_INDEX);

	asm volatile("isync":::"memory");
}