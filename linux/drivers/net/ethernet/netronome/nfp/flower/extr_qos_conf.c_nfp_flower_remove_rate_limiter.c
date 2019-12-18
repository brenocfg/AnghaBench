#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tc_cls_matchall_offload {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nfp_repr {TYPE_2__* app; struct nfp_flower_repr_priv* app_priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;
struct nfp_police_config {TYPE_1__ head; int /*<<< orphan*/  netdev_port_id; } ;
struct nfp_flower_repr_priv {struct nfp_police_config qos_table; } ;
struct nfp_flower_priv {int /*<<< orphan*/  qos_stats_work; int /*<<< orphan*/  qos_rate_limiters; } ;
struct nfp_fl_qos {int dummy; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_TYPE_QOS_DEL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nfp_police_config*,int /*<<< orphan*/ ,int) ; 
 struct nfp_repr* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nfp_ctrl_tx (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_buff* nfp_flower_cmsg_alloc (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfp_police_config* nfp_flower_cmsg_get_data (struct sk_buff*) ; 
 int /*<<< orphan*/  nfp_netdev_is_nfp_repr (struct net_device*) ; 
 int /*<<< orphan*/  nfp_repr_get_port_id (struct net_device*) ; 

__attribute__((used)) static int
nfp_flower_remove_rate_limiter(struct nfp_app *app, struct net_device *netdev,
			       struct tc_cls_matchall_offload *flow,
			       struct netlink_ext_ack *extack)
{
	struct nfp_flower_priv *fl_priv = app->priv;
	struct nfp_flower_repr_priv *repr_priv;
	struct nfp_police_config *config;
	struct nfp_repr *repr;
	struct sk_buff *skb;
	u32 netdev_port_id;

	if (!nfp_netdev_is_nfp_repr(netdev)) {
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: qos rate limit offload not supported on higher level port");
		return -EOPNOTSUPP;
	}
	repr = netdev_priv(netdev);

	netdev_port_id = nfp_repr_get_port_id(netdev);
	repr_priv = repr->app_priv;

	if (!repr_priv->qos_table.netdev_port_id) {
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: cannot remove qos entry that does not exist");
		return -EOPNOTSUPP;
	}

	skb = nfp_flower_cmsg_alloc(repr->app, sizeof(struct nfp_police_config),
				    NFP_FLOWER_CMSG_TYPE_QOS_DEL, GFP_KERNEL);
	if (!skb)
		return -ENOMEM;

	/* Clear all qos associate data for this interface */
	memset(&repr_priv->qos_table, 0, sizeof(struct nfp_fl_qos));
	fl_priv->qos_rate_limiters--;
	if (!fl_priv->qos_rate_limiters)
		cancel_delayed_work_sync(&fl_priv->qos_stats_work);

	config = nfp_flower_cmsg_get_data(skb);
	memset(config, 0, sizeof(struct nfp_police_config));
	config->head.port = cpu_to_be32(netdev_port_id);
	nfp_ctrl_tx(repr->app->ctrl, skb);

	return 0;
}