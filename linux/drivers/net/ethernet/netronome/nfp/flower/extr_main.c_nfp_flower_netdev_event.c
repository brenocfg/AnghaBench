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
struct nfp_flower_priv {int flower_ext_feats; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int NFP_FL_FEATS_LAG ; 
 int NOTIFY_STOP_MASK ; 
 int nfp_flower_internal_port_event_handler (struct nfp_app*,struct net_device*,unsigned long) ; 
 int nfp_flower_lag_netdev_event (struct nfp_flower_priv*,struct net_device*,unsigned long,void*) ; 
 int nfp_flower_reg_indir_block_handler (struct nfp_app*,struct net_device*,unsigned long) ; 
 int nfp_tunnel_mac_event_handler (struct nfp_app*,struct net_device*,unsigned long,void*) ; 

__attribute__((used)) static int
nfp_flower_netdev_event(struct nfp_app *app, struct net_device *netdev,
			unsigned long event, void *ptr)
{
	struct nfp_flower_priv *app_priv = app->priv;
	int ret;

	if (app_priv->flower_ext_feats & NFP_FL_FEATS_LAG) {
		ret = nfp_flower_lag_netdev_event(app_priv, netdev, event, ptr);
		if (ret & NOTIFY_STOP_MASK)
			return ret;
	}

	ret = nfp_flower_reg_indir_block_handler(app, netdev, event);
	if (ret & NOTIFY_STOP_MASK)
		return ret;

	ret = nfp_flower_internal_port_event_handler(app, netdev, event);
	if (ret & NOTIFY_STOP_MASK)
		return ret;

	return nfp_tunnel_mac_event_handler(app, netdev, event, ptr);
}