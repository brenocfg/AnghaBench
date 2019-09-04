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
struct TYPE_2__ {int /*<<< orphan*/  protocol; } ;
struct tc_cls_flower_offload {int command; TYPE_1__ common; } ;
struct nfp_app {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_CLSFLOWER_DESTROY 130 
#define  TC_CLSFLOWER_REPLACE 129 
#define  TC_CLSFLOWER_STATS 128 
 int /*<<< orphan*/  eth_proto_is_802_3 (int /*<<< orphan*/ ) ; 
 int nfp_flower_add_offload (struct nfp_app*,struct net_device*,struct tc_cls_flower_offload*,int) ; 
 int nfp_flower_del_offload (struct nfp_app*,struct net_device*,struct tc_cls_flower_offload*,int) ; 
 int nfp_flower_get_stats (struct nfp_app*,struct net_device*,struct tc_cls_flower_offload*,int) ; 

__attribute__((used)) static int
nfp_flower_repr_offload(struct nfp_app *app, struct net_device *netdev,
			struct tc_cls_flower_offload *flower, bool egress)
{
	if (!eth_proto_is_802_3(flower->common.protocol))
		return -EOPNOTSUPP;

	switch (flower->command) {
	case TC_CLSFLOWER_REPLACE:
		return nfp_flower_add_offload(app, netdev, flower, egress);
	case TC_CLSFLOWER_DESTROY:
		return nfp_flower_del_offload(app, netdev, flower, egress);
	case TC_CLSFLOWER_STATS:
		return nfp_flower_get_stats(app, netdev, flower, egress);
	default:
		return -EOPNOTSUPP;
	}
}