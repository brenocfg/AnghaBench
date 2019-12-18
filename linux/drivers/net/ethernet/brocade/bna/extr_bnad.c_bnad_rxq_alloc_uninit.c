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
struct bnad_rx_unmap_q {int reuse_pi; int alloc_order; int /*<<< orphan*/  type; scalar_t__ map_size; } ;
struct bnad {int dummy; } ;
struct bna_rcb {struct bnad_rx_unmap_q* unmap_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNAD_RXBUF_NONE ; 

__attribute__((used)) static inline void
bnad_rxq_alloc_uninit(struct bnad *bnad, struct bna_rcb *rcb)
{
	struct bnad_rx_unmap_q *unmap_q = rcb->unmap_q;

	unmap_q->reuse_pi = -1;
	unmap_q->alloc_order = -1;
	unmap_q->map_size = 0;
	unmap_q->type = BNAD_RXBUF_NONE;
}