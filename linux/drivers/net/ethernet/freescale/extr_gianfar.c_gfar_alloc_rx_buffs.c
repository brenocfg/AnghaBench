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
struct rxbd8 {int dummy; } ;
struct gfar_rx_buff {scalar_t__ page_offset; scalar_t__ dma; int /*<<< orphan*/  page; } ;
struct gfar_priv_rx_q {int next_to_use; int rx_ring_size; int next_to_alloc; struct gfar_rx_buff* rx_buff; struct rxbd8* rx_bd_base; } ;

/* Variables and functions */
 scalar_t__ RXBUF_ALIGNMENT ; 
 int /*<<< orphan*/  gfar_init_rxbdp (struct gfar_priv_rx_q*,struct rxbd8*,scalar_t__) ; 
 int /*<<< orphan*/  gfar_new_page (struct gfar_priv_rx_q*,struct gfar_rx_buff*) ; 
 int /*<<< orphan*/  gfar_rx_alloc_err (struct gfar_priv_rx_q*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void gfar_alloc_rx_buffs(struct gfar_priv_rx_q *rx_queue,
				int alloc_cnt)
{
	struct rxbd8 *bdp;
	struct gfar_rx_buff *rxb;
	int i;

	i = rx_queue->next_to_use;
	bdp = &rx_queue->rx_bd_base[i];
	rxb = &rx_queue->rx_buff[i];

	while (alloc_cnt--) {
		/* try reuse page */
		if (unlikely(!rxb->page)) {
			if (unlikely(!gfar_new_page(rx_queue, rxb))) {
				gfar_rx_alloc_err(rx_queue);
				break;
			}
		}

		/* Setup the new RxBD */
		gfar_init_rxbdp(rx_queue, bdp,
				rxb->dma + rxb->page_offset + RXBUF_ALIGNMENT);

		/* Update to the next pointer */
		bdp++;
		rxb++;

		if (unlikely(++i == rx_queue->rx_ring_size)) {
			i = 0;
			bdp = rx_queue->rx_bd_base;
			rxb = rx_queue->rx_buff;
		}
	}

	rx_queue->next_to_use = i;
	rx_queue->next_to_alloc = i;
}