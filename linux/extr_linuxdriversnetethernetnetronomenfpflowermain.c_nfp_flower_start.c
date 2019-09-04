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
 int nfp_flower_lag_reset (TYPE_1__*) ; 
 int nfp_tunnel_config_start (struct nfp_app*) ; 
 int register_netdevice_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfp_flower_start(struct nfp_app *app)
{
	struct nfp_flower_priv *app_priv = app->priv;
	int err;

	if (app_priv->flower_ext_feats & NFP_FL_FEATS_LAG) {
		err = nfp_flower_lag_reset(&app_priv->nfp_lag);
		if (err)
			return err;

		err = register_netdevice_notifier(&app_priv->nfp_lag.lag_nb);
		if (err)
			return err;
	}

	return nfp_tunnel_config_start(app);
}