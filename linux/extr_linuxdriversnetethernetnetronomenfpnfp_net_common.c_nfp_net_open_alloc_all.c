#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int num_r_vecs; } ;
struct nfp_net {int max_r_vecs; int /*<<< orphan*/ * r_vecs; TYPE_2__ dp; TYPE_1__* irq_entries; int /*<<< orphan*/  lsc_handler; int /*<<< orphan*/  lsc_name; int /*<<< orphan*/  exn_handler; int /*<<< orphan*/  exn_name; } ;
struct TYPE_6__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_NET_CFG_EXN ; 
 int /*<<< orphan*/  NFP_NET_CFG_LSC ; 
 size_t NFP_NET_IRQ_EXN_IDX ; 
 size_t NFP_NET_IRQ_LSC_IDX ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_net_aux_irq_free (struct nfp_net*,int /*<<< orphan*/ ,size_t) ; 
 int nfp_net_aux_irq_request (struct nfp_net*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_net_cleanup_vector (struct nfp_net*,int /*<<< orphan*/ *) ; 
 int nfp_net_prepare_vector (struct nfp_net*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfp_net_rx_rings_free (TYPE_2__*) ; 
 int nfp_net_rx_rings_prepare (struct nfp_net*,TYPE_2__*) ; 
 int nfp_net_tx_rings_prepare (struct nfp_net*,TYPE_2__*) ; 
 int /*<<< orphan*/  nfp_net_vector_assign_rings (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int nfp_net_open_alloc_all(struct nfp_net *nn)
{
	int err, r;

	err = nfp_net_aux_irq_request(nn, NFP_NET_CFG_EXN, "%s-exn",
				      nn->exn_name, sizeof(nn->exn_name),
				      NFP_NET_IRQ_EXN_IDX, nn->exn_handler);
	if (err)
		return err;
	err = nfp_net_aux_irq_request(nn, NFP_NET_CFG_LSC, "%s-lsc",
				      nn->lsc_name, sizeof(nn->lsc_name),
				      NFP_NET_IRQ_LSC_IDX, nn->lsc_handler);
	if (err)
		goto err_free_exn;
	disable_irq(nn->irq_entries[NFP_NET_IRQ_LSC_IDX].vector);

	for (r = 0; r < nn->dp.num_r_vecs; r++) {
		err = nfp_net_prepare_vector(nn, &nn->r_vecs[r], r);
		if (err)
			goto err_cleanup_vec_p;
	}

	err = nfp_net_rx_rings_prepare(nn, &nn->dp);
	if (err)
		goto err_cleanup_vec;

	err = nfp_net_tx_rings_prepare(nn, &nn->dp);
	if (err)
		goto err_free_rx_rings;

	for (r = 0; r < nn->max_r_vecs; r++)
		nfp_net_vector_assign_rings(&nn->dp, &nn->r_vecs[r], r);

	return 0;

err_free_rx_rings:
	nfp_net_rx_rings_free(&nn->dp);
err_cleanup_vec:
	r = nn->dp.num_r_vecs;
err_cleanup_vec_p:
	while (r--)
		nfp_net_cleanup_vector(nn, &nn->r_vecs[r]);
	nfp_net_aux_irq_free(nn, NFP_NET_CFG_LSC, NFP_NET_IRQ_LSC_IDX);
err_free_exn:
	nfp_net_aux_irq_free(nn, NFP_NET_CFG_EXN, NFP_NET_IRQ_EXN_IDX);
	return err;
}