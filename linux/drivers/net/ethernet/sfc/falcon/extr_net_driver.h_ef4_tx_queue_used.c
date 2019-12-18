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
struct ef4_tx_queue {int queue; TYPE_2__* efx; } ;
struct TYPE_4__ {TYPE_1__* net_dev; } ;
struct TYPE_3__ {int num_tc; } ;

/* Variables and functions */
 int EF4_TXQ_TYPE_HIGHPRI ; 

__attribute__((used)) static inline bool ef4_tx_queue_used(struct ef4_tx_queue *tx_queue)
{
	return !(tx_queue->efx->net_dev->num_tc < 2 &&
		 tx_queue->queue & EF4_TXQ_TYPE_HIGHPRI);
}