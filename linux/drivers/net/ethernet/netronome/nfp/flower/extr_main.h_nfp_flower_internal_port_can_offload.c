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
struct nfp_flower_priv {int flower_ext_feats; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct net_device {TYPE_1__* rtnl_link_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 int NFP_FL_FEATS_FLOW_MERGE ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline bool
nfp_flower_internal_port_can_offload(struct nfp_app *app,
				     struct net_device *netdev)
{
	struct nfp_flower_priv *app_priv = app->priv;

	if (!(app_priv->flower_ext_feats & NFP_FL_FEATS_FLOW_MERGE))
		return false;
	if (!netdev->rtnl_link_ops)
		return false;
	if (!strcmp(netdev->rtnl_link_ops->kind, "openvswitch"))
		return true;

	return false;
}