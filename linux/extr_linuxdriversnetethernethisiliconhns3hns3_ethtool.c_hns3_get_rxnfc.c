#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rss_size; } ;
struct hnae3_handle {TYPE_3__* ae_algo; TYPE_1__ kinfo; } ;
struct ethtool_rxnfc {int cmd; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int (* get_rss_tuple ) (struct hnae3_handle*,struct ethtool_rxnfc*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_GRXFH 129 
#define  ETHTOOL_GRXRINGS 128 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 int stub1 (struct hnae3_handle*,struct ethtool_rxnfc*) ; 

__attribute__((used)) static int hns3_get_rxnfc(struct net_device *netdev,
			  struct ethtool_rxnfc *cmd,
			  u32 *rule_locs)
{
	struct hnae3_handle *h = hns3_get_handle(netdev);

	if (!h->ae_algo || !h->ae_algo->ops || !h->ae_algo->ops->get_rss_tuple)
		return -EOPNOTSUPP;

	switch (cmd->cmd) {
	case ETHTOOL_GRXRINGS:
		cmd->data = h->kinfo.rss_size;
		break;
	case ETHTOOL_GRXFH:
		return h->ae_algo->ops->get_rss_tuple(h, cmd);
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}