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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct bnx2_rx_bd {int rx_bd_flags; int rx_bd_haddr_hi; int rx_bd_haddr_lo; int /*<<< orphan*/  rx_bd_len; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int BNX2_MAX_RX_DESC_CNT ; 
 int RX_BD_FLAGS_END ; 
 int RX_BD_FLAGS_START ; 

__attribute__((used)) static void
bnx2_init_rxbd_rings(struct bnx2_rx_bd *rx_ring[], dma_addr_t dma[],
		     u32 buf_size, int num_rings)
{
	int i;
	struct bnx2_rx_bd *rxbd;

	for (i = 0; i < num_rings; i++) {
		int j;

		rxbd = &rx_ring[i][0];
		for (j = 0; j < BNX2_MAX_RX_DESC_CNT; j++, rxbd++) {
			rxbd->rx_bd_len = buf_size;
			rxbd->rx_bd_flags = RX_BD_FLAGS_START | RX_BD_FLAGS_END;
		}
		if (i == (num_rings - 1))
			j = 0;
		else
			j = i + 1;
		rxbd->rx_bd_haddr_hi = (u64) dma[j] >> 32;
		rxbd->rx_bd_haddr_lo = (u64) dma[j] & 0xffffffff;
	}
}