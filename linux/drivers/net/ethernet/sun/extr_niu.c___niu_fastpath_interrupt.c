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
typedef  int u32 ;
struct tx_ring_info {int tx_channel; } ;
struct rx_ring_info {int rx_channel; } ;
struct niu_parent {int* ldg_map; } ;
struct niu {int num_rx_rings; int num_tx_rings; struct tx_ring_info* tx_rings; struct rx_ring_info* rx_rings; struct niu_parent* parent; } ;

/* Variables and functions */
 int LDN_RXDMA (int) ; 
 int LDN_TXDMA (int) ; 
 int /*<<< orphan*/  LD_IM0 (int) ; 
 int /*<<< orphan*/  LD_IM0_MASK ; 
 int /*<<< orphan*/  niu_rxchan_intr (struct niu*,struct rx_ring_info*,int) ; 
 int /*<<< orphan*/  niu_txchan_intr (struct niu*,struct tx_ring_info*,int) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __niu_fastpath_interrupt(struct niu *np, int ldg, u64 v0)
{
	struct niu_parent *parent = np->parent;
	u32 rx_vec, tx_vec;
	int i;

	tx_vec = (v0 >> 32);
	rx_vec = (v0 & 0xffffffff);

	for (i = 0; i < np->num_rx_rings; i++) {
		struct rx_ring_info *rp = &np->rx_rings[i];
		int ldn = LDN_RXDMA(rp->rx_channel);

		if (parent->ldg_map[ldn] != ldg)
			continue;

		nw64(LD_IM0(ldn), LD_IM0_MASK);
		if (rx_vec & (1 << rp->rx_channel))
			niu_rxchan_intr(np, rp, ldn);
	}

	for (i = 0; i < np->num_tx_rings; i++) {
		struct tx_ring_info *rp = &np->tx_rings[i];
		int ldn = LDN_TXDMA(rp->tx_channel);

		if (parent->ldg_map[ldn] != ldg)
			continue;

		nw64(LD_IM0(ldn), LD_IM0_MASK);
		if (tx_vec & (1 << rp->tx_channel))
			niu_txchan_intr(np, rp, ldn);
	}
}