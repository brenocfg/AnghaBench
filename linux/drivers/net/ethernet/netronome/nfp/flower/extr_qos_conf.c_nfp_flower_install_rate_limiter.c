#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_11__ {int prio; } ;
struct tc_cls_matchall_offload {TYPE_3__ common; TYPE_2__* rule; } ;
struct sk_buff {int dummy; } ;
struct nfp_repr {TYPE_7__* app; TYPE_1__* port; struct nfp_flower_repr_priv* app_priv; } ;
struct TYPE_13__ {void* port; } ;
struct nfp_police_config {void* cir; void* pir; void* cbs; void* pbs; void* bkt_tkn_c; void* bkt_tkn_p; TYPE_5__ head; } ;
struct TYPE_14__ {int netdev_port_id; } ;
struct nfp_flower_repr_priv {TYPE_6__ qos_table; scalar_t__ block_shared; } ;
struct nfp_flower_priv {int qos_rate_limiters; int /*<<< orphan*/  qos_stats_work; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_12__ {int rate_bytes_ps; int /*<<< orphan*/  burst; } ;
struct flow_action_entry {scalar_t__ id; TYPE_4__ police; } ;
struct TYPE_16__ {struct flow_action_entry* entries; } ;
struct TYPE_15__ {int /*<<< orphan*/  ctrl; } ;
struct TYPE_10__ {TYPE_8__ action; } ;
struct TYPE_9__ {scalar_t__ type; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 scalar_t__ FLOW_ACTION_POLICE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_TYPE_QOS_MOD ; 
 int /*<<< orphan*/  NFP_FL_QOS_UPDATE ; 
 scalar_t__ NFP_PORT_VF_PORT ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int PSCHED_NS2TICKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSCHED_TICKS_PER_SEC ; 
 void* cpu_to_be32 (int) ; 
 int div_u64 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_offload_has_one_action (TYPE_8__*) ; 
 int /*<<< orphan*/  memset (struct nfp_police_config*,int /*<<< orphan*/ ,int) ; 
 struct nfp_repr* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nfp_ctrl_tx (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_buff* nfp_flower_cmsg_alloc (TYPE_7__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfp_police_config* nfp_flower_cmsg_get_data (struct sk_buff*) ; 
 int /*<<< orphan*/  nfp_netdev_is_nfp_repr (struct net_device*) ; 
 int nfp_repr_get_port_id (struct net_device*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_flower_install_rate_limiter(struct nfp_app *app, struct net_device *netdev,
				struct tc_cls_matchall_offload *flow,
				struct netlink_ext_ack *extack)
{
	struct flow_action_entry *action = &flow->rule->action.entries[0];
	struct nfp_flower_priv *fl_priv = app->priv;
	struct nfp_flower_repr_priv *repr_priv;
	struct nfp_police_config *config;
	struct nfp_repr *repr;
	struct sk_buff *skb;
	u32 netdev_port_id;
	u64 burst, rate;

	if (!nfp_netdev_is_nfp_repr(netdev)) {
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: qos rate limit offload not supported on higher level port");
		return -EOPNOTSUPP;
	}
	repr = netdev_priv(netdev);
	repr_priv = repr->app_priv;

	if (repr_priv->block_shared) {
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: qos rate limit offload not supported on shared blocks");
		return -EOPNOTSUPP;
	}

	if (repr->port->type != NFP_PORT_VF_PORT) {
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: qos rate limit offload not supported on non-VF ports");
		return -EOPNOTSUPP;
	}

	if (!flow_offload_has_one_action(&flow->rule->action)) {
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: qos rate limit offload requires a single action");
		return -EOPNOTSUPP;
	}

	if (flow->common.prio != 1) {
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: qos rate limit offload requires highest priority");
		return -EOPNOTSUPP;
	}

	if (action->id != FLOW_ACTION_POLICE) {
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: qos rate limit offload requires police action");
		return -EOPNOTSUPP;
	}

	rate = action->police.rate_bytes_ps;
	burst = div_u64(rate * PSCHED_NS2TICKS(action->police.burst),
			PSCHED_TICKS_PER_SEC);
	netdev_port_id = nfp_repr_get_port_id(netdev);

	skb = nfp_flower_cmsg_alloc(repr->app, sizeof(struct nfp_police_config),
				    NFP_FLOWER_CMSG_TYPE_QOS_MOD, GFP_KERNEL);
	if (!skb)
		return -ENOMEM;

	config = nfp_flower_cmsg_get_data(skb);
	memset(config, 0, sizeof(struct nfp_police_config));
	config->head.port = cpu_to_be32(netdev_port_id);
	config->bkt_tkn_p = cpu_to_be32(burst);
	config->bkt_tkn_c = cpu_to_be32(burst);
	config->pbs = cpu_to_be32(burst);
	config->cbs = cpu_to_be32(burst);
	config->pir = cpu_to_be32(rate);
	config->cir = cpu_to_be32(rate);
	nfp_ctrl_tx(repr->app->ctrl, skb);

	repr_priv->qos_table.netdev_port_id = netdev_port_id;
	fl_priv->qos_rate_limiters++;
	if (fl_priv->qos_rate_limiters == 1)
		schedule_delayed_work(&fl_priv->qos_stats_work,
				      NFP_FL_QOS_UPDATE);

	return 0;
}