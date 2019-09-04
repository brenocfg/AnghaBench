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
struct x86_mapping_info {int direct_gbpages; int /*<<< orphan*/  kernpg_flag; int /*<<< orphan*/  page_flag; struct kimage* context; int /*<<< orphan*/  alloc_pgt_page; } ;
struct kimage {int nr_segments; TYPE_1__* segment; } ;
typedef  int /*<<< orphan*/  pgd_t ;
struct TYPE_4__ {unsigned long start; unsigned long end; } ;
struct TYPE_3__ {unsigned long mem; unsigned long memsz; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  _KERNPG_TABLE_NOENC ; 
 int /*<<< orphan*/  __PAGE_KERNEL_LARGE_EXEC ; 
 scalar_t__ __va (unsigned long) ; 
 int /*<<< orphan*/  alloc_pgt_page ; 
 int /*<<< orphan*/  clear_page (int /*<<< orphan*/ *) ; 
 scalar_t__ direct_gbpages ; 
 int init_transition_pgtable (struct kimage*,int /*<<< orphan*/ *) ; 
 int kernel_ident_mapping_init (struct x86_mapping_info*,int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int nr_pfn_mapped ; 
 TYPE_2__* pfn_mapped ; 

__attribute__((used)) static int init_pgtable(struct kimage *image, unsigned long start_pgtable)
{
	struct x86_mapping_info info = {
		.alloc_pgt_page	= alloc_pgt_page,
		.context	= image,
		.page_flag	= __PAGE_KERNEL_LARGE_EXEC,
		.kernpg_flag	= _KERNPG_TABLE_NOENC,
	};
	unsigned long mstart, mend;
	pgd_t *level4p;
	int result;
	int i;

	level4p = (pgd_t *)__va(start_pgtable);
	clear_page(level4p);

	if (direct_gbpages)
		info.direct_gbpages = true;

	for (i = 0; i < nr_pfn_mapped; i++) {
		mstart = pfn_mapped[i].start << PAGE_SHIFT;
		mend   = pfn_mapped[i].end << PAGE_SHIFT;

		result = kernel_ident_mapping_init(&info,
						 level4p, mstart, mend);
		if (result)
			return result;
	}

	/*
	 * segments's mem ranges could be outside 0 ~ max_pfn,
	 * for example when jump back to original kernel from kexeced kernel.
	 * or first kernel is booted with user mem map, and second kernel
	 * could be loaded out of that range.
	 */
	for (i = 0; i < image->nr_segments; i++) {
		mstart = image->segment[i].mem;
		mend   = mstart + image->segment[i].memsz;

		result = kernel_ident_mapping_init(&info,
						 level4p, mstart, mend);

		if (result)
			return result;
	}

	return init_transition_pgtable(image, level4p);
}