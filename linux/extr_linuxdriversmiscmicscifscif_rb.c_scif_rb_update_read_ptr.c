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
struct scif_rb {int /*<<< orphan*/ * read_ptr; int /*<<< orphan*/  current_read_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 

void scif_rb_update_read_ptr(struct scif_rb *rb)
{
	u32 new_offset;

	new_offset = rb->current_read_offset;
	/*
	 * We must ensure ordering between the all the data committed or read
	 * previously before we expose the empty slot to the peer by updating
	 * the read_ptr. This barrier is paired with the memory barrier in
	 * scif_rb_space(..)
	 */
	mb();
	WRITE_ONCE(*rb->read_ptr, new_offset);
#ifdef CONFIG_INTEL_MIC_CARD
	/*
	 * X100 Si Bug: For the case where a Core is performing an EXT_WR
	 * followed by a Doorbell Write, the Core must perform two EXT_WR to the
	 * same address with the same data before it does the Doorbell Write.
	 * This way, if ordering is violated for the Interrupt Message, it will
	 * fall just behind the first Posted associated with the first EXT_WR.
	 */
	WRITE_ONCE(*rb->read_ptr, new_offset);
#endif
}