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
struct nfp_reprs {int dummy; } ;
struct nfp_pf {scalar_t__ max_data_vnics; int /*<<< orphan*/  mac_stats_bar; TYPE_1__* eth_tbl; int /*<<< orphan*/  cpp; } ;
struct nfp_app {struct nfp_abm* priv; int /*<<< orphan*/ * reprs; int /*<<< orphan*/  cpp; struct nfp_pf* pf; } ;
struct nfp_abm {int /*<<< orphan*/  threshold_undef; void* thresholds; void* actions; int /*<<< orphan*/  num_thresholds; int /*<<< orphan*/  num_bands; struct nfp_app* app; } ;
struct TYPE_2__ {scalar_t__ count; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFP_NET_MAX_RX_RINGS ; 
 size_t NFP_REPR_TYPE_PF ; 
 size_t NFP_REPR_TYPE_PHYS_PORT ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct nfp_reprs*) ; 
 int /*<<< orphan*/  array_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfp_abm*) ; 
 void* kvcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 struct nfp_abm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nfp_abm_ctrl_find_addrs (struct nfp_abm*) ; 
 int nfp_abm_fw_init_reset (struct nfp_abm*) ; 
 int /*<<< orphan*/  nfp_err (int /*<<< orphan*/ ,char*,...) ; 
 struct nfp_reprs* nfp_reprs_alloc (scalar_t__) ; 
 int /*<<< orphan*/  nfp_reprs_clean_and_free_by_type (struct nfp_app*,size_t) ; 
 int /*<<< orphan*/  nfp_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int nfp_abm_init(struct nfp_app *app)
{
	struct nfp_pf *pf = app->pf;
	struct nfp_reprs *reprs;
	struct nfp_abm *abm;
	int err;

	if (!pf->eth_tbl) {
		nfp_err(pf->cpp, "ABM NIC requires ETH table\n");
		return -EINVAL;
	}
	if (pf->max_data_vnics != pf->eth_tbl->count) {
		nfp_err(pf->cpp, "ETH entries don't match vNICs (%d vs %d)\n",
			pf->max_data_vnics, pf->eth_tbl->count);
		return -EINVAL;
	}
	if (!pf->mac_stats_bar) {
		nfp_warn(app->cpp, "ABM NIC requires mac_stats symbol\n");
		return -EINVAL;
	}

	abm = kzalloc(sizeof(*abm), GFP_KERNEL);
	if (!abm)
		return -ENOMEM;
	app->priv = abm;
	abm->app = app;

	err = nfp_abm_ctrl_find_addrs(abm);
	if (err)
		goto err_free_abm;

	err = -ENOMEM;
	abm->num_thresholds = array_size(abm->num_bands, NFP_NET_MAX_RX_RINGS);
	abm->threshold_undef = bitmap_zalloc(abm->num_thresholds, GFP_KERNEL);
	if (!abm->threshold_undef)
		goto err_free_abm;

	abm->thresholds = kvcalloc(abm->num_thresholds,
				   sizeof(*abm->thresholds), GFP_KERNEL);
	if (!abm->thresholds)
		goto err_free_thresh_umap;

	abm->actions = kvcalloc(abm->num_thresholds, sizeof(*abm->actions),
				GFP_KERNEL);
	if (!abm->actions)
		goto err_free_thresh;

	/* We start in legacy mode, make sure advanced queuing is disabled */
	err = nfp_abm_fw_init_reset(abm);
	if (err)
		goto err_free_act;

	err = -ENOMEM;
	reprs = nfp_reprs_alloc(pf->max_data_vnics);
	if (!reprs)
		goto err_free_act;
	RCU_INIT_POINTER(app->reprs[NFP_REPR_TYPE_PHYS_PORT], reprs);

	reprs = nfp_reprs_alloc(pf->max_data_vnics);
	if (!reprs)
		goto err_free_phys;
	RCU_INIT_POINTER(app->reprs[NFP_REPR_TYPE_PF], reprs);

	return 0;

err_free_phys:
	nfp_reprs_clean_and_free_by_type(app, NFP_REPR_TYPE_PHYS_PORT);
err_free_act:
	kvfree(abm->actions);
err_free_thresh:
	kvfree(abm->thresholds);
err_free_thresh_umap:
	bitmap_free(abm->threshold_undef);
err_free_abm:
	kfree(abm);
	app->priv = NULL;
	return err;
}