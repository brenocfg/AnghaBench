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
struct sw_rx_bd {int /*<<< orphan*/  data; } ;
struct eth_rx_bd {int dummy; } ;
struct bnx2x_fastpath {struct eth_rx_bd* rx_desc_ring; struct sw_rx_bd* rx_buf_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_unmap_addr (struct sw_rx_bd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct sw_rx_bd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping ; 

__attribute__((used)) static inline void bnx2x_reuse_rx_data(struct bnx2x_fastpath *fp,
				      u16 cons, u16 prod)
{
	struct sw_rx_bd *cons_rx_buf = &fp->rx_buf_ring[cons];
	struct sw_rx_bd *prod_rx_buf = &fp->rx_buf_ring[prod];
	struct eth_rx_bd *cons_bd = &fp->rx_desc_ring[cons];
	struct eth_rx_bd *prod_bd = &fp->rx_desc_ring[prod];

	dma_unmap_addr_set(prod_rx_buf, mapping,
			   dma_unmap_addr(cons_rx_buf, mapping));
	prod_rx_buf->data = cons_rx_buf->data;
	*prod_bd = *cons_bd;
}