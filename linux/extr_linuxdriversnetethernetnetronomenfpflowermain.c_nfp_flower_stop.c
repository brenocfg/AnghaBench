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
struct TYPE_2__ {int /*<<< orphan*/  lag_nb; } ;
struct nfp_flower_priv {int flower_ext_feats; TYPE_1__ nfp_lag; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;

/* Variables and functions */
 int NFP_FL_FEATS_LAG ; 
 int /*<<< orphan*/  nfp_tunnel_config_stop (struct nfp_app*) ; 
 int /*<<< orphan*/  unregister_netdevice_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfp_flower_stop(struct nfp_app *app)
{
	struct nfp_flower_priv *app_priv = app->priv;

	if (app_priv->flower_ext_feats & NFP_FL_FEATS_LAG)
		unregister_netdevice_notifier(&app_priv->nfp_lag.lag_nb);

	nfp_tunnel_config_stop(app);
}