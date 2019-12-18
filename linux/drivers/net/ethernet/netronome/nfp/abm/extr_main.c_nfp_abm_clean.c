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
struct nfp_app {struct nfp_abm* priv; } ;
struct nfp_abm {int /*<<< orphan*/  thresholds; int /*<<< orphan*/  actions; int /*<<< orphan*/  threshold_undef; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_REPR_TYPE_PF ; 
 int /*<<< orphan*/  NFP_REPR_TYPE_PHYS_PORT ; 
 int /*<<< orphan*/  bitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfp_abm*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_abm_eswitch_clean_up (struct nfp_abm*) ; 
 int /*<<< orphan*/  nfp_reprs_clean_and_free_by_type (struct nfp_app*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_abm_clean(struct nfp_app *app)
{
	struct nfp_abm *abm = app->priv;

	nfp_abm_eswitch_clean_up(abm);
	nfp_reprs_clean_and_free_by_type(app, NFP_REPR_TYPE_PF);
	nfp_reprs_clean_and_free_by_type(app, NFP_REPR_TYPE_PHYS_PORT);
	bitmap_free(abm->threshold_undef);
	kvfree(abm->actions);
	kvfree(abm->thresholds);
	kfree(abm);
	app->priv = NULL;
}