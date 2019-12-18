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
struct fifo {int nrents; int imask; scalar_t__* fifobar; int /*<<< orphan*/  merge; scalar_t__ reset; scalar_t__ tail; scalar_t__ head; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_MASK_O ; 

__attribute__((used)) static void fifo_setup(void *base_addr, int nr_entry)
{
	struct fifo *fifo_q = base_addr;
	int i;

	/* set up an empty fifo */
	fifo_q->head = 0;
	fifo_q->tail = 0;
	fifo_q->reset = 0;
	fifo_q->nrents = nr_entry;
	fifo_q->imask = nr_entry - 1;
	fifo_q->merge = ENTRY_MASK_O;

	for (i = 0; i < nr_entry; i++)
		fifo_q->fifobar[i] = 0;
}