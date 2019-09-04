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
struct nfp_pf {scalar_t__ max_data_vnics; TYPE_1__* eth_tbl; int /*<<< orphan*/  cpp; } ;
struct nfp_net {struct nfp_bpf_vnic* app_priv; } ;
struct nfp_bpf_vnic {void* tgt_done; void* start_off; } ;
struct nfp_app {struct nfp_pf* pf; } ;
struct TYPE_2__ {scalar_t__ count; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFP_NET_CFG_BPF_DONE ; 
 int /*<<< orphan*/  NFP_NET_CFG_BPF_START ; 
 int /*<<< orphan*/  kfree (struct nfp_bpf_vnic*) ; 
 struct nfp_bpf_vnic* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nfp_app_nic_vnic_alloc (struct nfp_app*,struct nfp_net*,unsigned int) ; 
 int /*<<< orphan*/  nfp_err (int /*<<< orphan*/ ,char*,...) ; 
 void* nn_readw (struct nfp_net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_bpf_vnic_alloc(struct nfp_app *app, struct nfp_net *nn, unsigned int id)
{
	struct nfp_pf *pf = app->pf;
	struct nfp_bpf_vnic *bv;
	int err;

	if (!pf->eth_tbl) {
		nfp_err(pf->cpp, "No ETH table\n");
		return -EINVAL;
	}
	if (pf->max_data_vnics != pf->eth_tbl->count) {
		nfp_err(pf->cpp, "ETH entries don't match vNICs (%d vs %d)\n",
			pf->max_data_vnics, pf->eth_tbl->count);
		return -EINVAL;
	}

	bv = kzalloc(sizeof(*bv), GFP_KERNEL);
	if (!bv)
		return -ENOMEM;
	nn->app_priv = bv;

	err = nfp_app_nic_vnic_alloc(app, nn, id);
	if (err)
		goto err_free_priv;

	bv->start_off = nn_readw(nn, NFP_NET_CFG_BPF_START);
	bv->tgt_done = nn_readw(nn, NFP_NET_CFG_BPF_DONE);

	return 0;
err_free_priv:
	kfree(nn->app_priv);
	return err;
}