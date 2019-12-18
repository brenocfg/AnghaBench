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
typedef  int /*<<< orphan*/  u32 ;
struct scif_rb {int /*<<< orphan*/  size; int /*<<< orphan*/  current_read_offset; int /*<<< orphan*/  current_write_offset; int /*<<< orphan*/ * read_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  scif_rb_ring_space (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32 scif_rb_space(struct scif_rb *rb)
{
	rb->current_read_offset = *rb->read_ptr;
	/*
	 * Update from the HW read pointer only once the peer has exposed the
	 * new empty slot. This barrier is paired with the memory barrier
	 * scif_rb_update_read_ptr()
	 */
	mb();
	return scif_rb_ring_space(rb->current_write_offset,
				  rb->current_read_offset, rb->size);
}