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
struct TYPE_6__ {TYPE_2__* fifos; } ;
struct TYPE_4__ {int tx_fifo_num; int /*<<< orphan*/  multiq; } ;
struct s2io_nic {int /*<<< orphan*/  dev; TYPE_3__ mac_control; TYPE_1__ config; } ;
struct TYPE_5__ {int /*<<< orphan*/  queue_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIFO_QUEUE_STOP ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void s2io_stop_all_tx_queue(struct s2io_nic *sp)
{
	if (!sp->config.multiq) {
		int i;

		for (i = 0; i < sp->config.tx_fifo_num; i++)
			sp->mac_control.fifos[i].queue_state = FIFO_QUEUE_STOP;
	}
	netif_tx_stop_all_queues(sp->dev);
}