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
struct TYPE_6__ {scalar_t__ lstatus; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
union enetc_rx_bd {TYPE_3__ r; TYPE_2__ w; } ;
struct enetc_rx_swbd {scalar_t__ page_offset; scalar_t__ dma; int /*<<< orphan*/  page; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_alloc_errs; } ;
struct enetc_bdr {int next_to_use; int bd_count; int next_to_alloc; int /*<<< orphan*/  rcir; struct enetc_rx_swbd* rx_swbd; TYPE_1__ stats; } ;

/* Variables and functions */
 union enetc_rx_bd* ENETC_RXBD (struct enetc_bdr,int) ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  enetc_new_page (struct enetc_bdr*,struct enetc_rx_swbd*) ; 
 int /*<<< orphan*/  enetc_wr_reg (int /*<<< orphan*/ ,int) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int enetc_refill_rx_ring(struct enetc_bdr *rx_ring, const int buff_cnt)
{
	struct enetc_rx_swbd *rx_swbd;
	union enetc_rx_bd *rxbd;
	int i, j;

	i = rx_ring->next_to_use;
	rx_swbd = &rx_ring->rx_swbd[i];
	rxbd = ENETC_RXBD(*rx_ring, i);

	for (j = 0; j < buff_cnt; j++) {
		/* try reuse page */
		if (unlikely(!rx_swbd->page)) {
			if (unlikely(!enetc_new_page(rx_ring, rx_swbd))) {
				rx_ring->stats.rx_alloc_errs++;
				break;
			}
		}

		/* update RxBD */
		rxbd->w.addr = cpu_to_le64(rx_swbd->dma +
					   rx_swbd->page_offset);
		/* clear 'R" as well */
		rxbd->r.lstatus = 0;

		rx_swbd++;
		rxbd++;
		i++;
		if (unlikely(i == rx_ring->bd_count)) {
			i = 0;
			rx_swbd = rx_ring->rx_swbd;
			rxbd = ENETC_RXBD(*rx_ring, 0);
		}
	}

	if (likely(j)) {
		rx_ring->next_to_alloc = i; /* keep track from page reuse */
		rx_ring->next_to_use = i;
		/* update ENETC's consumer index */
		enetc_wr_reg(rx_ring->rcir, i);
	}

	return j;
}