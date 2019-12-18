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
struct TYPE_4__ {int /*<<< orphan*/  completed; } ;
struct TYPE_3__ {int /*<<< orphan*/  req_cons; int /*<<< orphan*/  rsp_prod_pvt; } ;
struct xenvif_queue {TYPE_2__ rx_copy; TYPE_1__ rx; } ;
struct xenvif_pkt_state {int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xenvif_rx_complete(struct xenvif_queue *queue,
			       struct xenvif_pkt_state *pkt)
{
	/* All responses are ready to be pushed. */
	queue->rx.rsp_prod_pvt = queue->rx.req_cons;

	__skb_queue_tail(queue->rx_copy.completed, pkt->skb);
}