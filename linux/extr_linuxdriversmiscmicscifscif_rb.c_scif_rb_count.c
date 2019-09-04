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
typedef  scalar_t__ u32 ;
struct scif_rb {int /*<<< orphan*/  size; int /*<<< orphan*/  current_read_offset; int /*<<< orphan*/  current_write_offset; int /*<<< orphan*/ * write_ptr; } ;

/* Variables and functions */
 scalar_t__ scif_rb_ring_cnt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 

u32 scif_rb_count(struct scif_rb *rb, u32 size)
{
	if (scif_rb_ring_cnt(rb->current_write_offset,
			     rb->current_read_offset,
			     rb->size) < size) {
		rb->current_write_offset = *rb->write_ptr;
		/*
		 * Update from the HW write pointer if empty only once the peer
		 * has exposed the new message. This read barrier is paired
		 * with the write barrier in scif_rb_commit(..)
		 */
		smp_rmb();
	}
	return scif_rb_ring_cnt(rb->current_write_offset,
				rb->current_read_offset,
				rb->size);
}