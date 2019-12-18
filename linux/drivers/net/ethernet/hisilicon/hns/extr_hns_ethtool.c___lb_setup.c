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
struct phy_device {int dummy; } ;
struct net_device {int flags; struct phy_device* phydev; } ;
struct hns_nic_priv {struct hnae_handle* ae_handle; } ;
struct hnae_handle {TYPE_2__* dev; int /*<<< orphan*/  phy_if; } ;
typedef  enum hnae_loop { ____Placeholder_hnae_loop } hnae_loop ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* set_loopback ) (struct hnae_handle*,int,int) ;int /*<<< orphan*/  (* set_promisc_mode ) (struct hnae_handle*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int IFF_PROMISC ; 
#define  MAC_INTERNALLOOP_MAC 132 
#define  MAC_INTERNALLOOP_PHY 131 
#define  MAC_INTERNALLOOP_SERDES 130 
#define  MAC_LOOP_NONE 129 
#define  MAC_LOOP_PHY_NONE 128 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_XGMII ; 
 int hns_nic_config_phy_loopback (struct phy_device*,int) ; 
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 
 int stub1 (struct hnae_handle*,int,int) ; 
 int stub2 (struct hnae_handle*,int,int) ; 
 int stub3 (struct hnae_handle*,int,int) ; 
 int stub4 (struct hnae_handle*,int const,int) ; 
 int stub5 (struct hnae_handle*,int const,int) ; 
 int /*<<< orphan*/  stub6 (struct hnae_handle*,int) ; 
 int /*<<< orphan*/  stub7 (struct hnae_handle*,int) ; 

__attribute__((used)) static int __lb_setup(struct net_device *ndev,
		      enum hnae_loop loop)
{
	int ret = 0;
	struct hns_nic_priv *priv = netdev_priv(ndev);
	struct phy_device *phy_dev = ndev->phydev;
	struct hnae_handle *h = priv->ae_handle;

	switch (loop) {
	case MAC_INTERNALLOOP_PHY:
		ret = hns_nic_config_phy_loopback(phy_dev, 0x1);
		if (!ret)
			ret = h->dev->ops->set_loopback(h, loop, 0x1);
		break;
	case MAC_INTERNALLOOP_MAC:
		if ((h->dev->ops->set_loopback) &&
		    (priv->ae_handle->phy_if != PHY_INTERFACE_MODE_XGMII))
			ret = h->dev->ops->set_loopback(h, loop, 0x1);
		break;
	case MAC_INTERNALLOOP_SERDES:
		if (h->dev->ops->set_loopback)
			ret = h->dev->ops->set_loopback(h, loop, 0x1);
		break;
	case MAC_LOOP_PHY_NONE:
		ret = hns_nic_config_phy_loopback(phy_dev, 0x0);
		/* fall through */
	case MAC_LOOP_NONE:
		if (!ret && h->dev->ops->set_loopback) {
			if (priv->ae_handle->phy_if != PHY_INTERFACE_MODE_XGMII)
				ret = h->dev->ops->set_loopback(h,
					MAC_INTERNALLOOP_MAC, 0x0);

			if (!ret)
				ret = h->dev->ops->set_loopback(h,
					MAC_INTERNALLOOP_SERDES, 0x0);
		}
		break;
	default:
		ret = -EINVAL;
		break;
	}

	if (!ret) {
		if (loop == MAC_LOOP_NONE)
			h->dev->ops->set_promisc_mode(
				h, ndev->flags & IFF_PROMISC);
		else
			h->dev->ops->set_promisc_mode(h, 1);
	}
	return ret;
}