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
struct lan743x_tx {scalar_t__* head_cpu_ptr; scalar_t__ last_head; } ;

/* Variables and functions */
 scalar_t__ lan743x_tx_next_index (struct lan743x_tx*,scalar_t__) ; 
 int /*<<< orphan*/  lan743x_tx_release_desc (struct lan743x_tx*,scalar_t__,int) ; 

__attribute__((used)) static void lan743x_tx_release_completed_descriptors(struct lan743x_tx *tx)
{
	while ((*tx->head_cpu_ptr) != (tx->last_head)) {
		lan743x_tx_release_desc(tx, tx->last_head, false);
		tx->last_head = lan743x_tx_next_index(tx, tx->last_head);
	}
}