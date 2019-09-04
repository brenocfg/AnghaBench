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
struct net_device {int dummy; } ;
struct hnae3_handle {TYPE_2__* ae_algo; } ;
struct ethtool_rxnfc {int cmd; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* set_rss_tuple ) (struct hnae3_handle*,struct ethtool_rxnfc*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_SRXFH 128 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 int stub1 (struct hnae3_handle*,struct ethtool_rxnfc*) ; 

__attribute__((used)) static int hns3_set_rxnfc(struct net_device *netdev, struct ethtool_rxnfc *cmd)
{
	struct hnae3_handle *h = hns3_get_handle(netdev);

	if (!h->ae_algo || !h->ae_algo->ops || !h->ae_algo->ops->set_rss_tuple)
		return -EOPNOTSUPP;

	switch (cmd->cmd) {
	case ETHTOOL_SRXFH:
		return h->ae_algo->ops->set_rss_tuple(h, cmd);
	default:
		return -EOPNOTSUPP;
	}
}