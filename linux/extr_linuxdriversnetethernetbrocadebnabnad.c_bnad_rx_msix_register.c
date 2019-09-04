#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct bnad_rx_info {TYPE_3__* rx_ctrl; } ;
struct bnad {TYPE_2__* msix_table; TYPE_1__* netdev; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;
struct TYPE_8__ {int intr_vector; int id; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_4__* ccb; } ;
struct TYPE_6__ {int /*<<< orphan*/  vector; } ;
struct TYPE_5__ {char* name; } ;

/* Variables and functions */
 scalar_t__ bnad_msix_rx ; 
 int /*<<< orphan*/  bnad_rx_msix_unregister (struct bnad*,struct bnad_rx_info*,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static int
bnad_rx_msix_register(struct bnad *bnad, struct bnad_rx_info *rx_info,
			u32 rx_id, int num_rxps)
{
	int i;
	int err;
	int vector_num;

	for (i = 0; i < num_rxps; i++) {
		vector_num = rx_info->rx_ctrl[i].ccb->intr_vector;
		sprintf(rx_info->rx_ctrl[i].ccb->name, "%s CQ %d",
			bnad->netdev->name,
			rx_id + rx_info->rx_ctrl[i].ccb->id);
		err = request_irq(bnad->msix_table[vector_num].vector,
				  (irq_handler_t)bnad_msix_rx, 0,
				  rx_info->rx_ctrl[i].ccb->name,
				  rx_info->rx_ctrl[i].ccb);
		if (err)
			goto err_return;
	}

	return 0;

err_return:
	if (i > 0)
		bnad_rx_msix_unregister(bnad, rx_info, (i - 1));
	return -1;
}