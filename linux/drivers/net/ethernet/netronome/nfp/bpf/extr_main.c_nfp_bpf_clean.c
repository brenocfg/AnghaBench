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
struct nfp_app_bpf {int /*<<< orphan*/  maps_neutral; scalar_t__ map_elems_in_use; scalar_t__ maps_in_use; int /*<<< orphan*/  map_list; int /*<<< orphan*/  ccm; int /*<<< orphan*/  bpf_dev; } ;
struct nfp_app {struct nfp_app_bpf* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bpf_offload_dev_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfp_app_bpf*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_ccm_clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_check_rhashtable_empty ; 
 int /*<<< orphan*/  rhashtable_free_and_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfp_bpf_clean(struct nfp_app *app)
{
	struct nfp_app_bpf *bpf = app->priv;

	bpf_offload_dev_destroy(bpf->bpf_dev);
	nfp_ccm_clean(&bpf->ccm);
	WARN_ON(!list_empty(&bpf->map_list));
	WARN_ON(bpf->maps_in_use || bpf->map_elems_in_use);
	rhashtable_free_and_destroy(&bpf->maps_neutral,
				    nfp_check_rhashtable_empty, NULL);
	kfree(bpf);
}