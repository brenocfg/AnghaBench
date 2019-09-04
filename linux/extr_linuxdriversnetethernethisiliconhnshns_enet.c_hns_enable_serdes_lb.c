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
struct net_device {int dummy; } ;
struct hns_nic_priv {struct hnae_handle* ae_handle; } ;
struct hnae_handle {scalar_t__ phy_if; TYPE_1__* dev; } ;
struct hnae_ae_ops {int (* set_loopback ) (struct hnae_handle*,int /*<<< orphan*/ ,int) ;int (* start ) (struct hnae_handle*) ;int /*<<< orphan*/  (* adjust_link ) (struct hnae_handle*,int,int) ;} ;
struct TYPE_2__ {struct hnae_ae_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_INTERNALLOOP_SERDES ; 
 scalar_t__ PHY_INTERFACE_MODE_XGMII ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 
 int stub1 (struct hnae_handle*,int /*<<< orphan*/ ,int) ; 
 int stub2 (struct hnae_handle*) ; 
 int /*<<< orphan*/  stub3 (struct hnae_handle*,int,int) ; 

__attribute__((used)) static int hns_enable_serdes_lb(struct net_device *ndev)
{
	struct hns_nic_priv *priv = netdev_priv(ndev);
	struct hnae_handle *h = priv->ae_handle;
	struct hnae_ae_ops *ops = h->dev->ops;
	int speed, duplex;
	int ret;

	ret = ops->set_loopback(h, MAC_INTERNALLOOP_SERDES, 1);
	if (ret)
		return ret;

	ret = ops->start ? ops->start(h) : 0;
	if (ret)
		return ret;

	/* link adjust duplex*/
	if (h->phy_if != PHY_INTERFACE_MODE_XGMII)
		speed = 1000;
	else
		speed = 10000;
	duplex = 1;

	ops->adjust_link(h, speed, duplex);

	/* wait h/w ready */
	mdelay(300);

	return 0;
}