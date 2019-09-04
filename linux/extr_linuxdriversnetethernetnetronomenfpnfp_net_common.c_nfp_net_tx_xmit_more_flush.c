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
struct nfp_net_tx_ring {scalar_t__ wr_ptr_add; int /*<<< orphan*/  qcp_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfp_qcp_wr_ptr_add (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void nfp_net_tx_xmit_more_flush(struct nfp_net_tx_ring *tx_ring)
{
	wmb();
	nfp_qcp_wr_ptr_add(tx_ring->qcp_q, tx_ring->wr_ptr_add);
	tx_ring->wr_ptr_add = 0;
}