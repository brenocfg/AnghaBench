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
typedef  int u32 ;
struct net_device {TYPE_3__* phydev; } ;
struct hns_nic_priv {int link; struct hnae_handle* ae_handle; } ;
struct hnae_handle {TYPE_2__* dev; } ;
struct TYPE_6__ {int link; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {scalar_t__ (* get_status ) (struct hnae_handle*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  genphy_read_status (TYPE_3__*) ; 
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ stub1 (struct hnae_handle*) ; 

__attribute__((used)) static u32 hns_nic_get_link(struct net_device *net_dev)
{
	struct hns_nic_priv *priv = netdev_priv(net_dev);
	u32 link_stat = priv->link;
	struct hnae_handle *h;

	h = priv->ae_handle;

	if (net_dev->phydev) {
		if (!genphy_read_status(net_dev->phydev))
			link_stat = net_dev->phydev->link;
		else
			link_stat = 0;
	}

	if (h->dev && h->dev->ops && h->dev->ops->get_status)
		link_stat = link_stat && h->dev->ops->get_status(h);
	else
		link_stat = 0;

	return link_stat;
}