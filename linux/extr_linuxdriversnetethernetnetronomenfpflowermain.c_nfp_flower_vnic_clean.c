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
struct nfp_net {int dummy; } ;
struct nfp_flower_priv {int /*<<< orphan*/ * nn; } ;
struct nfp_app {TYPE_1__* pf; struct nfp_flower_priv* priv; } ;
struct TYPE_2__ {scalar_t__ num_vfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_REPR_TYPE_PF ; 
 int /*<<< orphan*/  NFP_REPR_TYPE_PHYS_PORT ; 
 int /*<<< orphan*/  NFP_REPR_TYPE_VF ; 
 int /*<<< orphan*/  nfp_reprs_clean_and_free_by_type (struct nfp_app*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_flower_vnic_clean(struct nfp_app *app, struct nfp_net *nn)
{
	struct nfp_flower_priv *priv = app->priv;

	if (app->pf->num_vfs)
		nfp_reprs_clean_and_free_by_type(app, NFP_REPR_TYPE_VF);
	nfp_reprs_clean_and_free_by_type(app, NFP_REPR_TYPE_PF);
	nfp_reprs_clean_and_free_by_type(app, NFP_REPR_TYPE_PHYS_PORT);

	priv->nn = NULL;
}