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
struct pvrdma_ring {int /*<<< orphan*/  cons_head; int /*<<< orphan*/  prod_tail; } ;
typedef  int __u32 ;
typedef  int __s32 ;

/* Variables and functions */
 int PVRDMA_INVALID_IDX ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ pvrdma_idx_valid (int const,int) ; 

__attribute__((used)) static inline __s32 pvrdma_idx_ring_has_space(const struct pvrdma_ring *r,
					      __u32 max_elems, __u32 *out_tail)
{
	const __u32 tail = atomic_read(&r->prod_tail);
	const __u32 head = atomic_read(&r->cons_head);

	if (pvrdma_idx_valid(tail, max_elems) &&
	    pvrdma_idx_valid(head, max_elems)) {
		*out_tail = tail & (max_elems - 1);
		return tail != (head ^ max_elems);
	}
	return PVRDMA_INVALID_IDX;
}