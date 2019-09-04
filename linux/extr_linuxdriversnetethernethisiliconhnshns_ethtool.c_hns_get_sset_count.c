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
typedef  int u32 ;
struct net_device {TYPE_1__* phydev; } ;
struct hns_nic_priv {struct hnae_handle* ae_handle; } ;
struct hnae_handle {scalar_t__ phy_if; TYPE_2__* dev; } ;
struct hnae_ae_ops {int (* get_sset_count ) (struct hnae_handle*,int) ;} ;
typedef  int /*<<< orphan*/  hns_nic_test_strs ;
struct TYPE_4__ {struct hnae_ae_ops* ops; } ;
struct TYPE_3__ {scalar_t__ is_c45; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int ETH_GSTRING_LEN ; 
 int ETH_SS_STATS ; 
 int ETH_SS_TEST ; 
 int HNS_NET_STATS_CNT ; 
 scalar_t__ PHY_INTERFACE_MODE_XGMII ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 
 int stub1 (struct hnae_handle*,int) ; 

__attribute__((used)) static int hns_get_sset_count(struct net_device *netdev, int stringset)
{
	struct hns_nic_priv *priv = netdev_priv(netdev);
	struct hnae_handle *h = priv->ae_handle;
	struct hnae_ae_ops *ops = h->dev->ops;

	if (!ops->get_sset_count) {
		netdev_err(netdev, "get_sset_count is null!\n");
		return -EOPNOTSUPP;
	}
	if (stringset == ETH_SS_TEST) {
		u32 cnt = (sizeof(hns_nic_test_strs) / ETH_GSTRING_LEN);

		if (priv->ae_handle->phy_if == PHY_INTERFACE_MODE_XGMII)
			cnt--;

		if ((!netdev->phydev) || (netdev->phydev->is_c45))
			cnt--;

		return cnt;
	} else if (stringset == ETH_SS_STATS) {
		return (HNS_NET_STATS_CNT + ops->get_sset_count(h, stringset));
	} else {
		return -EOPNOTSUPP;
	}
}