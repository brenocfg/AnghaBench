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
struct hns_nic_priv {struct hnae_handle* ae_handle; } ;
struct hnae_handle {scalar_t__ phy_if; TYPE_2__* dev; } ;
typedef  enum hnae_loop { ____Placeholder_hnae_loop } hnae_loop ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* start ) (struct hnae_handle*) ;int /*<<< orphan*/  (* adjust_link ) (struct hnae_handle*,int,int) ;} ;

/* Variables and functions */
 int NIC_LB_TEST_WAIT_PHY_LINK_TIME ; 
 scalar_t__ PHY_INTERFACE_MODE_XGMII ; 
 int __lb_setup (struct net_device*,int) ; 
 int /*<<< orphan*/  hns_nic_net_reset (struct net_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 
 int stub1 (struct hnae_handle*) ; 
 int /*<<< orphan*/  stub2 (struct hnae_handle*,int,int) ; 

__attribute__((used)) static int __lb_up(struct net_device *ndev,
		   enum hnae_loop loop_mode)
{
#define NIC_LB_TEST_WAIT_PHY_LINK_TIME 300
	struct hns_nic_priv *priv = netdev_priv(ndev);
	struct hnae_handle *h = priv->ae_handle;
	int speed, duplex;
	int ret;

	hns_nic_net_reset(ndev);

	ret = __lb_setup(ndev, loop_mode);
	if (ret)
		return ret;

	msleep(200);

	ret = h->dev->ops->start ? h->dev->ops->start(h) : 0;
	if (ret)
		return ret;

	/* link adjust duplex*/
	if (priv->ae_handle->phy_if != PHY_INTERFACE_MODE_XGMII)
		speed = 1000;
	else
		speed = 10000;
	duplex = 1;

	h->dev->ops->adjust_link(h, speed, duplex);

	/* wait adjust link done and phy ready */
	msleep(NIC_LB_TEST_WAIT_PHY_LINK_TIME);

	return 0;
}