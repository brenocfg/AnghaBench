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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_INTR ; 
 int FST_MAX_CARDS ; 
 int /*<<< orphan*/  dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  do_bottom_half_rx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_bottom_half_tx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** fst_card_array ; 
 int fst_work_intq ; 
 int /*<<< orphan*/  fst_work_q_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
fst_process_int_work_q(unsigned long /*void **/work_q)
{
	unsigned long flags;
	u64 work_intq;
	int i;

	/*
	 * Grab the queue exclusively
	 */
	dbg(DBG_INTR, "fst_process_int_work_q\n");
	spin_lock_irqsave(&fst_work_q_lock, flags);
	work_intq = fst_work_intq;
	fst_work_intq = 0;
	spin_unlock_irqrestore(&fst_work_q_lock, flags);

	/*
	 * Call the bottom half for each card with work waiting
	 */
	for (i = 0; i < FST_MAX_CARDS; i++) {
		if (work_intq & 0x01) {
			if (fst_card_array[i] != NULL) {
				dbg(DBG_INTR,
				    "Calling rx & tx bh for card %d\n", i);
				do_bottom_half_rx(fst_card_array[i]);
				do_bottom_half_tx(fst_card_array[i]);
			}
		}
		work_intq = work_intq >> 1;
	}
}