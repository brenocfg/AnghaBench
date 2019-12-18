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
struct TYPE_4__ {int req_cons; TYPE_1__* sring; } ;
struct xenvif_queue {scalar_t__ stalled; TYPE_2__ rx; } ;
struct TYPE_3__ {int req_prod; } ;
typedef  int RING_IDX ;

/* Variables and functions */

__attribute__((used)) static bool xenvif_rx_queue_ready(struct xenvif_queue *queue)
{
	RING_IDX prod, cons;

	prod = queue->rx.sring->req_prod;
	cons = queue->rx.req_cons;

	return queue->stalled && prod - cons >= 1;
}