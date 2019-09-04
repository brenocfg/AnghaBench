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
struct nfp_net_tx_ring {int wr_p; int rd_p; int cnt; } ;

/* Variables and functions */

__attribute__((used)) static int nfp_net_tx_full(struct nfp_net_tx_ring *tx_ring, int dcnt)
{
	return (tx_ring->wr_p - tx_ring->rd_p) >= (tx_ring->cnt - dcnt);
}