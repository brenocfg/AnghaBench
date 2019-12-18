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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct rx_bd {scalar_t__ rx_bd_opaque; int /*<<< orphan*/  rx_bd_haddr; } ;
struct rx_agg_cmp {scalar_t__ rx_agg_cmp_opaque; } ;
struct page {int dummy; } ;
struct bnxt_sw_rx_agg_bd {int /*<<< orphan*/  mapping; int /*<<< orphan*/  offset; struct page* page; } ;
struct bnxt_rx_ring_info {scalar_t__ rx_agg_prod; scalar_t__ rx_sw_agg_prod; struct rx_bd** rx_agg_desc_ring; struct bnxt_sw_rx_agg_bd* rx_agg_ring; int /*<<< orphan*/  rx_agg_bmap; } ;
struct bnxt_napi {struct bnxt_rx_ring_info* rx_ring; struct bnxt* bp; } ;
struct bnxt_cp_ring_info {struct bnxt_napi* bnapi; } ;
struct bnxt {int flags; } ;

/* Variables and functions */
 int BNXT_FLAG_CHIP_P5 ; 
 scalar_t__ NEXT_RX_AGG (scalar_t__) ; 
 size_t RX_IDX (scalar_t__) ; 
 size_t RX_RING (scalar_t__) ; 
 int /*<<< orphan*/  __clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ bnxt_find_next_agg_idx (struct bnxt_rx_ring_info*,scalar_t__) ; 
 struct rx_agg_cmp* bnxt_get_agg (struct bnxt*,struct bnxt_cp_ring_info*,scalar_t__,scalar_t__) ; 
 struct rx_agg_cmp* bnxt_get_tpa_agg_p5 (struct bnxt*,struct bnxt_rx_ring_info*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_reuse_rx_agg_bufs(struct bnxt_cp_ring_info *cpr, u16 idx,
				   u16 start, u32 agg_bufs, bool tpa)
{
	struct bnxt_napi *bnapi = cpr->bnapi;
	struct bnxt *bp = bnapi->bp;
	struct bnxt_rx_ring_info *rxr = bnapi->rx_ring;
	u16 prod = rxr->rx_agg_prod;
	u16 sw_prod = rxr->rx_sw_agg_prod;
	bool p5_tpa = false;
	u32 i;

	if ((bp->flags & BNXT_FLAG_CHIP_P5) && tpa)
		p5_tpa = true;

	for (i = 0; i < agg_bufs; i++) {
		u16 cons;
		struct rx_agg_cmp *agg;
		struct bnxt_sw_rx_agg_bd *cons_rx_buf, *prod_rx_buf;
		struct rx_bd *prod_bd;
		struct page *page;

		if (p5_tpa)
			agg = bnxt_get_tpa_agg_p5(bp, rxr, idx, start + i);
		else
			agg = bnxt_get_agg(bp, cpr, idx, start + i);
		cons = agg->rx_agg_cmp_opaque;
		__clear_bit(cons, rxr->rx_agg_bmap);

		if (unlikely(test_bit(sw_prod, rxr->rx_agg_bmap)))
			sw_prod = bnxt_find_next_agg_idx(rxr, sw_prod);

		__set_bit(sw_prod, rxr->rx_agg_bmap);
		prod_rx_buf = &rxr->rx_agg_ring[sw_prod];
		cons_rx_buf = &rxr->rx_agg_ring[cons];

		/* It is possible for sw_prod to be equal to cons, so
		 * set cons_rx_buf->page to NULL first.
		 */
		page = cons_rx_buf->page;
		cons_rx_buf->page = NULL;
		prod_rx_buf->page = page;
		prod_rx_buf->offset = cons_rx_buf->offset;

		prod_rx_buf->mapping = cons_rx_buf->mapping;

		prod_bd = &rxr->rx_agg_desc_ring[RX_RING(prod)][RX_IDX(prod)];

		prod_bd->rx_bd_haddr = cpu_to_le64(cons_rx_buf->mapping);
		prod_bd->rx_bd_opaque = sw_prod;

		prod = NEXT_RX_AGG(prod);
		sw_prod = NEXT_RX_AGG(sw_prod);
	}
	rxr->rx_agg_prod = prod;
	rxr->rx_sw_agg_prod = sw_prod;
}