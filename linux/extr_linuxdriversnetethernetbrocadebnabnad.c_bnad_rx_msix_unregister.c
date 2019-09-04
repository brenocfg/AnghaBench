#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bnad_rx_info {TYPE_2__* rx_ctrl; } ;
struct bnad {TYPE_1__* msix_table; } ;
struct TYPE_6__ {int intr_vector; } ;
struct TYPE_5__ {TYPE_3__* ccb; } ;
struct TYPE_4__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void
bnad_rx_msix_unregister(struct bnad *bnad, struct bnad_rx_info *rx_info,
			int num_rxps)
{
	int i;
	int vector_num;

	for (i = 0; i < num_rxps; i++) {
		if (rx_info->rx_ctrl[i].ccb == NULL)
			continue;

		vector_num = rx_info->rx_ctrl[i].ccb->intr_vector;
		free_irq(bnad->msix_table[vector_num].vector,
			 rx_info->rx_ctrl[i].ccb);
	}
}