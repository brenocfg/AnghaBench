#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bnad_tx_info {TYPE_2__** tcb; } ;
struct bnad {TYPE_1__* msix_table; } ;
struct TYPE_4__ {int intr_vector; } ;
struct TYPE_3__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void
bnad_tx_msix_unregister(struct bnad *bnad, struct bnad_tx_info *tx_info,
			int num_txqs)
{
	int i;
	int vector_num;

	for (i = 0; i < num_txqs; i++) {
		if (tx_info->tcb[i] == NULL)
			continue;

		vector_num = tx_info->tcb[i]->intr_vector;
		free_irq(bnad->msix_table[vector_num].vector, tx_info->tcb[i]);
	}
}