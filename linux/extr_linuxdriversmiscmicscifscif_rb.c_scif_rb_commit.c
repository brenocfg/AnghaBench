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
struct scif_rb {int /*<<< orphan*/  current_write_offset; int /*<<< orphan*/ * write_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

void scif_rb_commit(struct scif_rb *rb)
{
	/*
	 * We must ensure ordering between the all the data committed
	 * previously before we expose the new message to the peer by
	 * updating the write_ptr. This write barrier is paired with
	 * the read barrier in scif_rb_count(..)
	 */
	wmb();
	WRITE_ONCE(*rb->write_ptr, rb->current_write_offset);
#ifdef CONFIG_INTEL_MIC_CARD
	/*
	 * X100 Si bug: For the case where a Core is performing an EXT_WR
	 * followed by a Doorbell Write, the Core must perform two EXT_WR to the
	 * same address with the same data before it does the Doorbell Write.
	 * This way, if ordering is violated for the Interrupt Message, it will
	 * fall just behind the first Posted associated with the first EXT_WR.
	 */
	WRITE_ONCE(*rb->write_ptr, rb->current_write_offset);
#endif
}