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
struct nfp_flower_priv {int flower_ext_feats; int /*<<< orphan*/  nfp_lag; int /*<<< orphan*/  cmsg_work; int /*<<< orphan*/  cmsg_skbs_low; int /*<<< orphan*/  cmsg_skbs_high; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;

/* Variables and functions */
 int NFP_FL_FEATS_FLOW_MERGE ; 
 int NFP_FL_FEATS_LAG ; 
 int NFP_FL_FEATS_VF_RLIM ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_flower_internal_port_cleanup (struct nfp_flower_priv*) ; 
 int /*<<< orphan*/  nfp_flower_lag_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_flower_metadata_cleanup (struct nfp_app*) ; 
 int /*<<< orphan*/  nfp_flower_qos_cleanup (struct nfp_app*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (struct nfp_flower_priv*) ; 

__attribute__((used)) static void nfp_flower_clean(struct nfp_app *app)
{
	struct nfp_flower_priv *app_priv = app->priv;

	skb_queue_purge(&app_priv->cmsg_skbs_high);
	skb_queue_purge(&app_priv->cmsg_skbs_low);
	flush_work(&app_priv->cmsg_work);

	if (app_priv->flower_ext_feats & NFP_FL_FEATS_VF_RLIM)
		nfp_flower_qos_cleanup(app);

	if (app_priv->flower_ext_feats & NFP_FL_FEATS_LAG)
		nfp_flower_lag_cleanup(&app_priv->nfp_lag);

	if (app_priv->flower_ext_feats & NFP_FL_FEATS_FLOW_MERGE)
		nfp_flower_internal_port_cleanup(app_priv);

	nfp_flower_metadata_cleanup(app);
	vfree(app->priv);
	app->priv = NULL;
}