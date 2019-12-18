#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfp_net_tx_ring {TYPE_1__* r_vec; int /*<<< orphan*/  cnt; int /*<<< orphan*/  dma; } ;
struct nfp_net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_NET_CFG_TXR_ADDR (unsigned int) ; 
 int /*<<< orphan*/  NFP_NET_CFG_TXR_SZ (unsigned int) ; 
 int /*<<< orphan*/  NFP_NET_CFG_TXR_VEC (unsigned int) ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_writeb (struct nfp_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_writeq (struct nfp_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfp_net_tx_ring_hw_cfg_write(struct nfp_net *nn,
			     struct nfp_net_tx_ring *tx_ring, unsigned int idx)
{
	nn_writeq(nn, NFP_NET_CFG_TXR_ADDR(idx), tx_ring->dma);
	nn_writeb(nn, NFP_NET_CFG_TXR_SZ(idx), ilog2(tx_ring->cnt));
	nn_writeb(nn, NFP_NET_CFG_TXR_VEC(idx), tx_ring->r_vec->irq_entry);
}