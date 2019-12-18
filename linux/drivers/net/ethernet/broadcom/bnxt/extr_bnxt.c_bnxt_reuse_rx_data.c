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
typedef  size_t u16 ;
struct rx_bd {int /*<<< orphan*/  rx_bd_haddr; } ;
struct bnxt_sw_rx_bd {int /*<<< orphan*/  mapping; int /*<<< orphan*/  data_ptr; void* data; } ;
struct bnxt_rx_ring_info {size_t rx_prod; struct rx_bd** rx_desc_ring; struct bnxt_sw_rx_bd* rx_buf_ring; } ;

/* Variables and functions */
 size_t RX_IDX (size_t) ; 
 size_t RX_RING (size_t) ; 

void bnxt_reuse_rx_data(struct bnxt_rx_ring_info *rxr, u16 cons, void *data)
{
	u16 prod = rxr->rx_prod;
	struct bnxt_sw_rx_bd *cons_rx_buf, *prod_rx_buf;
	struct rx_bd *cons_bd, *prod_bd;

	prod_rx_buf = &rxr->rx_buf_ring[prod];
	cons_rx_buf = &rxr->rx_buf_ring[cons];

	prod_rx_buf->data = data;
	prod_rx_buf->data_ptr = cons_rx_buf->data_ptr;

	prod_rx_buf->mapping = cons_rx_buf->mapping;

	prod_bd = &rxr->rx_desc_ring[RX_RING(prod)][RX_IDX(prod)];
	cons_bd = &rxr->rx_desc_ring[RX_RING(cons)][RX_IDX(cons)];

	prod_bd->rx_bd_haddr = cons_bd->rx_bd_haddr;
}