#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ s32 ;
struct TYPE_3__ {int /*<<< orphan*/ * device_curr_frag; int /*<<< orphan*/ * driver_curr_frag; } ;
typedef  TYPE_1__ isl38xx_control_block ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ const ISL38XX_CB_MGMT_QSIZE ; 
#define  ISL38XX_CB_RX_DATA_HQ 133 
#define  ISL38XX_CB_RX_DATA_LQ 132 
#define  ISL38XX_CB_RX_MGMTQ 131 
 scalar_t__ const ISL38XX_CB_RX_QSIZE ; 
#define  ISL38XX_CB_TX_DATA_HQ 130 
#define  ISL38XX_CB_TX_DATA_LQ 129 
#define  ISL38XX_CB_TX_MGMTQ 128 
 scalar_t__ const ISL38XX_CB_TX_QSIZE ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

int
isl38xx_in_queue(isl38xx_control_block *cb, int queue)
{
	const s32 delta = (le32_to_cpu(cb->driver_curr_frag[queue]) -
			   le32_to_cpu(cb->device_curr_frag[queue]));

	/* determine the amount of fragments in the queue depending on the type
	 * of the queue, either transmit or receive */

	BUG_ON(delta < 0);	/* driver ptr must be ahead of device ptr */

	switch (queue) {
		/* send queues */
	case ISL38XX_CB_TX_MGMTQ:
		BUG_ON(delta > ISL38XX_CB_MGMT_QSIZE);
		/* fall through */

	case ISL38XX_CB_TX_DATA_LQ:
	case ISL38XX_CB_TX_DATA_HQ:
		BUG_ON(delta > ISL38XX_CB_TX_QSIZE);
		return delta;

		/* receive queues */
	case ISL38XX_CB_RX_MGMTQ:
		BUG_ON(delta > ISL38XX_CB_MGMT_QSIZE);
		return ISL38XX_CB_MGMT_QSIZE - delta;

	case ISL38XX_CB_RX_DATA_LQ:
	case ISL38XX_CB_RX_DATA_HQ:
		BUG_ON(delta > ISL38XX_CB_RX_QSIZE);
		return ISL38XX_CB_RX_QSIZE - delta;
	}
	BUG();
	return 0;
}