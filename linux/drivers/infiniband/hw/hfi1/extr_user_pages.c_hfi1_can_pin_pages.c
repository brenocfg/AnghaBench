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
typedef  unsigned long u32 ;
struct mm_struct {int /*<<< orphan*/  pinned_vm; } ;
struct hfi1_devdata {unsigned int num_rcv_contexts; unsigned int first_dyn_alloc_ctxt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IPC_LOCK ; 
 unsigned long DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 unsigned long atomic64_read (int /*<<< orphan*/ *) ; 
 unsigned long cache_size ; 
 int capable (int /*<<< orphan*/ ) ; 
 unsigned long rlimit (int /*<<< orphan*/ ) ; 

bool hfi1_can_pin_pages(struct hfi1_devdata *dd, struct mm_struct *mm,
			u32 nlocked, u32 npages)
{
	unsigned long ulimit = rlimit(RLIMIT_MEMLOCK), pinned, cache_limit,
		size = (cache_size * (1UL << 20)); /* convert to bytes */
	unsigned int usr_ctxts =
			dd->num_rcv_contexts - dd->first_dyn_alloc_ctxt;
	bool can_lock = capable(CAP_IPC_LOCK);

	/*
	 * Calculate per-cache size. The calculation below uses only a quarter
	 * of the available per-context limit. This leaves space for other
	 * pinning. Should we worry about shared ctxts?
	 */
	cache_limit = (ulimit / usr_ctxts) / 4;

	/* If ulimit isn't set to "unlimited" and is smaller than cache_size. */
	if (ulimit != (-1UL) && size > cache_limit)
		size = cache_limit;

	/* Convert to number of pages */
	size = DIV_ROUND_UP(size, PAGE_SIZE);

	pinned = atomic64_read(&mm->pinned_vm);

	/* First, check the absolute limit against all pinned pages. */
	if (pinned + npages >= ulimit && !can_lock)
		return false;

	return ((nlocked + npages) <= size) || can_lock;
}