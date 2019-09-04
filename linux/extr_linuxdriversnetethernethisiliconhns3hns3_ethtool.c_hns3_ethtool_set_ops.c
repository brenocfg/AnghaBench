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
struct net_device {int /*<<< orphan*/ * ethtool_ops; } ;
struct hnae3_handle {int flags; } ;

/* Variables and functions */
 int HNAE3_SUPPORT_VF ; 
 int /*<<< orphan*/  hns3_ethtool_ops ; 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 int /*<<< orphan*/  hns3vf_ethtool_ops ; 

void hns3_ethtool_set_ops(struct net_device *netdev)
{
	struct hnae3_handle *h = hns3_get_handle(netdev);

	if (h->flags & HNAE3_SUPPORT_VF)
		netdev->ethtool_ops = &hns3vf_ethtool_ops;
	else
		netdev->ethtool_ops = &hns3_ethtool_ops;
}