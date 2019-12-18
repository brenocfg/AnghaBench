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
struct lan743x_tx {int last_head; int last_tail; int ring_size; } ;

/* Variables and functions */

__attribute__((used)) static int lan743x_tx_get_avail_desc(struct lan743x_tx *tx)
{
	int last_head = tx->last_head;
	int last_tail = tx->last_tail;

	if (last_tail >= last_head)
		return tx->ring_size - last_tail + last_head - 1;
	else
		return last_head - last_tail - 1;
}