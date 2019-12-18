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
struct nfp_app {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  protocol; } ;
struct flow_cls_offload {int command; TYPE_1__ common; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  FLOW_CLS_DESTROY 130 
#define  FLOW_CLS_REPLACE 129 
#define  FLOW_CLS_STATS 128 
 int /*<<< orphan*/  eth_proto_is_802_3 (int /*<<< orphan*/ ) ; 
 int nfp_flower_add_offload (struct nfp_app*,struct net_device*,struct flow_cls_offload*) ; 
 int nfp_flower_del_offload (struct nfp_app*,struct net_device*,struct flow_cls_offload*) ; 
 int nfp_flower_get_stats (struct nfp_app*,struct net_device*,struct flow_cls_offload*) ; 

__attribute__((used)) static int
nfp_flower_repr_offload(struct nfp_app *app, struct net_device *netdev,
			struct flow_cls_offload *flower)
{
	if (!eth_proto_is_802_3(flower->common.protocol))
		return -EOPNOTSUPP;

	switch (flower->command) {
	case FLOW_CLS_REPLACE:
		return nfp_flower_add_offload(app, netdev, flower);
	case FLOW_CLS_DESTROY:
		return nfp_flower_del_offload(app, netdev, flower);
	case FLOW_CLS_STATS:
		return nfp_flower_get_stats(app, netdev, flower);
	default:
		return -EOPNOTSUPP;
	}
}