#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int num_r_vecs; } ;
struct nfp_net {int /*<<< orphan*/ * r_vecs; TYPE_1__ dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_NET_CFG_EXN ; 
 int /*<<< orphan*/  NFP_NET_CFG_LSC ; 
 int /*<<< orphan*/  NFP_NET_IRQ_EXN_IDX ; 
 int /*<<< orphan*/  NFP_NET_IRQ_LSC_IDX ; 
 int /*<<< orphan*/  nfp_net_aux_irq_free (struct nfp_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_net_cleanup_vector (struct nfp_net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_net_rx_rings_free (TYPE_1__*) ; 
 int /*<<< orphan*/  nfp_net_tx_rings_free (TYPE_1__*) ; 

__attribute__((used)) static void nfp_net_close_free_all(struct nfp_net *nn)
{
	unsigned int r;

	nfp_net_tx_rings_free(&nn->dp);
	nfp_net_rx_rings_free(&nn->dp);

	for (r = 0; r < nn->dp.num_r_vecs; r++)
		nfp_net_cleanup_vector(nn, &nn->r_vecs[r]);

	nfp_net_aux_irq_free(nn, NFP_NET_CFG_LSC, NFP_NET_IRQ_LSC_IDX);
	nfp_net_aux_irq_free(nn, NFP_NET_CFG_EXN, NFP_NET_IRQ_EXN_IDX);
}