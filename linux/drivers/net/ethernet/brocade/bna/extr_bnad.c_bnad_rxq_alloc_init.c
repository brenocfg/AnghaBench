#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bnad_rx_unmap_q {int alloc_order; int map_size; int /*<<< orphan*/  type; } ;
struct bnad {int dummy; } ;
struct bna_rcb {TYPE_1__* rxq; int /*<<< orphan*/  id; struct bnad_rx_unmap_q* unmap_q; } ;
struct TYPE_2__ {int buffer_size; scalar_t__ multi_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNAD_RXBUF_MULTI_BUFF ; 
 int /*<<< orphan*/  BNAD_RXBUF_PAGE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PAGE_SIZE ; 
 scalar_t__ bna_is_small_rxq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnad_rxq_alloc_uninit (struct bnad*,struct bna_rcb*) ; 
 int get_order (int) ; 

__attribute__((used)) static int
bnad_rxq_alloc_init(struct bnad *bnad, struct bna_rcb *rcb)
{
	struct bnad_rx_unmap_q *unmap_q = rcb->unmap_q;
	int order;

	bnad_rxq_alloc_uninit(bnad, rcb);

	order = get_order(rcb->rxq->buffer_size);

	unmap_q->type = BNAD_RXBUF_PAGE;

	if (bna_is_small_rxq(rcb->id)) {
		unmap_q->alloc_order = 0;
		unmap_q->map_size = rcb->rxq->buffer_size;
	} else {
		if (rcb->rxq->multi_buffer) {
			unmap_q->alloc_order = 0;
			unmap_q->map_size = rcb->rxq->buffer_size;
			unmap_q->type = BNAD_RXBUF_MULTI_BUFF;
		} else {
			unmap_q->alloc_order = order;
			unmap_q->map_size =
				(rcb->rxq->buffer_size > 2048) ?
				PAGE_SIZE << order : 2048;
		}
	}

	BUG_ON((PAGE_SIZE << order) % unmap_q->map_size);

	return 0;
}