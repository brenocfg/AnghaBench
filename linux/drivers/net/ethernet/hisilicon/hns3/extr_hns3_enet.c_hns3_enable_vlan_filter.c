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
struct net_device {int dummy; } ;
struct hns3_nic_priv {struct hnae3_handle* ae_handle; } ;
struct hnae3_handle {int netdev_flags; TYPE_3__* ae_algo; TYPE_1__* pdev; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* enable_vlan_filter ) (struct hnae3_handle*,int) ;} ;
struct TYPE_4__ {int revision; } ;

/* Variables and functions */
 int HNAE3_VLAN_FLTR ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,char*) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct hnae3_handle*,int) ; 

void hns3_enable_vlan_filter(struct net_device *netdev, bool enable)
{
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	struct hnae3_handle *h = priv->ae_handle;
	bool last_state;

	if (h->pdev->revision >= 0x21 && h->ae_algo->ops->enable_vlan_filter) {
		last_state = h->netdev_flags & HNAE3_VLAN_FLTR ? true : false;
		if (enable != last_state) {
			netdev_info(netdev,
				    "%s vlan filter\n",
				    enable ? "enable" : "disable");
			h->ae_algo->ops->enable_vlan_filter(h, enable);
		}
	}
}