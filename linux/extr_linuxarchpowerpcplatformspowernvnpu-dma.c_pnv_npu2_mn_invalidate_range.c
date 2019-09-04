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
struct npu_context {int dummy; } ;
struct mmu_notifier {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 unsigned long atsd_threshold ; 
 int /*<<< orphan*/  mmio_invalidate (struct npu_context*,int,unsigned long,int) ; 
 struct npu_context* mn_to_npu_context (struct mmu_notifier*) ; 

__attribute__((used)) static void pnv_npu2_mn_invalidate_range(struct mmu_notifier *mn,
					struct mm_struct *mm,
					unsigned long start, unsigned long end)
{
	struct npu_context *npu_context = mn_to_npu_context(mn);
	unsigned long address;

	if (end - start > atsd_threshold) {
		/*
		 * Just invalidate the entire PID if the address range is too
		 * large.
		 */
		mmio_invalidate(npu_context, 0, 0, true);
	} else {
		for (address = start; address < end; address += PAGE_SIZE)
			mmio_invalidate(npu_context, 1, address, false);

		/* Do the flush only on the final addess == end */
		mmio_invalidate(npu_context, 1, address, true);
	}
}