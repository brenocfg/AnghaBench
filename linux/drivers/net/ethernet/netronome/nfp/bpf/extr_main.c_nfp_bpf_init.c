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
struct TYPE_2__ {int max_key_sz; int max_val_sz; } ;
struct nfp_app_bpf {int abi_version; int cmsg_key_sz; int cmsg_val_sz; int /*<<< orphan*/  ccm; int /*<<< orphan*/  maps_neutral; int /*<<< orphan*/  bpf_dev; TYPE_1__ maps; int /*<<< orphan*/  map_list; struct nfp_app* app; } ;
struct nfp_app {int /*<<< orphan*/  ctrl_mtu; struct nfp_app_bpf* priv; } ;

/* Variables and functions */
 int CMSG_MAP_KEY_LW ; 
 int CMSG_MAP_VALUE_LW ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_offload_dev_create (int /*<<< orphan*/ *,struct nfp_app_bpf*) ; 
 int /*<<< orphan*/  kfree (struct nfp_app_bpf*) ; 
 struct nfp_app_bpf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_bpf_ctrl_cmsg_mtu (struct nfp_app_bpf*) ; 
 int /*<<< orphan*/  nfp_bpf_dev_ops ; 
 int /*<<< orphan*/  nfp_bpf_init_capabilities (struct nfp_app_bpf*) ; 
 int /*<<< orphan*/  nfp_bpf_maps_neutral_params ; 
 int nfp_bpf_parse_capabilities (struct nfp_app*) ; 
 int /*<<< orphan*/  nfp_ccm_clean (int /*<<< orphan*/ *) ; 
 int nfp_ccm_init (int /*<<< orphan*/ *,struct nfp_app*) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 
 int rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfp_bpf_init(struct nfp_app *app)
{
	struct nfp_app_bpf *bpf;
	int err;

	bpf = kzalloc(sizeof(*bpf), GFP_KERNEL);
	if (!bpf)
		return -ENOMEM;
	bpf->app = app;
	app->priv = bpf;

	INIT_LIST_HEAD(&bpf->map_list);

	err = nfp_ccm_init(&bpf->ccm, app);
	if (err)
		goto err_free_bpf;

	err = rhashtable_init(&bpf->maps_neutral, &nfp_bpf_maps_neutral_params);
	if (err)
		goto err_clean_ccm;

	nfp_bpf_init_capabilities(bpf);

	err = nfp_bpf_parse_capabilities(app);
	if (err)
		goto err_free_neutral_maps;

	if (bpf->abi_version < 3) {
		bpf->cmsg_key_sz = CMSG_MAP_KEY_LW * 4;
		bpf->cmsg_val_sz = CMSG_MAP_VALUE_LW * 4;
	} else {
		bpf->cmsg_key_sz = bpf->maps.max_key_sz;
		bpf->cmsg_val_sz = bpf->maps.max_val_sz;
		app->ctrl_mtu = nfp_bpf_ctrl_cmsg_mtu(bpf);
	}

	bpf->bpf_dev = bpf_offload_dev_create(&nfp_bpf_dev_ops, bpf);
	err = PTR_ERR_OR_ZERO(bpf->bpf_dev);
	if (err)
		goto err_free_neutral_maps;

	return 0;

err_free_neutral_maps:
	rhashtable_destroy(&bpf->maps_neutral);
err_clean_ccm:
	nfp_ccm_clean(&bpf->ccm);
err_free_bpf:
	kfree(bpf);
	return err;
}