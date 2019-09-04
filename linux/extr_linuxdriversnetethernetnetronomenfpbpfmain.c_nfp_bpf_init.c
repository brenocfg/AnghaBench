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
struct nfp_app_bpf {int /*<<< orphan*/  maps_neutral; int /*<<< orphan*/  bpf_dev; int /*<<< orphan*/  map_list; int /*<<< orphan*/  cmsg_wq; int /*<<< orphan*/  cmsg_replies; struct nfp_app* app; } ;
struct nfp_app {struct nfp_app_bpf* priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_offload_dev_create () ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nfp_app_bpf*) ; 
 struct nfp_app_bpf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_bpf_maps_neutral_params ; 
 int nfp_bpf_parse_capabilities (struct nfp_app*) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 
 int rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfp_bpf_init(struct nfp_app *app)
{
	struct nfp_app_bpf *bpf;
	int err;

	bpf = kzalloc(sizeof(*bpf), GFP_KERNEL);
	if (!bpf)
		return -ENOMEM;
	bpf->app = app;
	app->priv = bpf;

	skb_queue_head_init(&bpf->cmsg_replies);
	init_waitqueue_head(&bpf->cmsg_wq);
	INIT_LIST_HEAD(&bpf->map_list);

	err = rhashtable_init(&bpf->maps_neutral, &nfp_bpf_maps_neutral_params);
	if (err)
		goto err_free_bpf;

	err = nfp_bpf_parse_capabilities(app);
	if (err)
		goto err_free_neutral_maps;

	bpf->bpf_dev = bpf_offload_dev_create();
	err = PTR_ERR_OR_ZERO(bpf->bpf_dev);
	if (err)
		goto err_free_neutral_maps;

	return 0;

err_free_neutral_maps:
	rhashtable_destroy(&bpf->maps_neutral);
err_free_bpf:
	kfree(bpf);
	return err;
}