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
struct nfp_flower_priv {int /*<<< orphan*/  nn; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_REPR_TYPE_VF ; 
 int /*<<< orphan*/  nfp_reprs_clean_and_free_by_type (struct nfp_app*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_flower_sriov_disable(struct nfp_app *app)
{
	struct nfp_flower_priv *priv = app->priv;

	if (!priv->nn)
		return;

	nfp_reprs_clean_and_free_by_type(app, NFP_REPR_TYPE_VF);
}