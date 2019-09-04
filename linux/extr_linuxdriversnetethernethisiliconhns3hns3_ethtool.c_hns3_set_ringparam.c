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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct hns3_nic_priv {struct hnae3_handle* ae_handle; } ;
struct TYPE_2__ {scalar_t__ num_desc; } ;
struct hnae3_handle {TYPE_1__ kinfo; } ;
struct ethtool_ringparam {scalar_t__ tx_pending; scalar_t__ rx_pending; scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  HNS3_RING_BD_MULTIPLE ; 
 scalar_t__ HNS3_RING_MAX_PENDING ; 
 scalar_t__ HNS3_RING_MIN_PENDING ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int dev_open (struct net_device*) ; 
 int hns3_change_all_ring_bd_num (struct hns3_nic_priv*,scalar_t__) ; 
 int hns3_uninit_all_ring (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,scalar_t__,scalar_t__) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int netif_running (struct net_device*) ; 

__attribute__((used)) static int hns3_set_ringparam(struct net_device *ndev,
			      struct ethtool_ringparam *param)
{
	struct hns3_nic_priv *priv = netdev_priv(ndev);
	struct hnae3_handle *h = priv->ae_handle;
	bool if_running = netif_running(ndev);
	u32 old_desc_num, new_desc_num;
	int ret;

	if (param->rx_mini_pending || param->rx_jumbo_pending)
		return -EINVAL;

	if (param->tx_pending != param->rx_pending) {
		netdev_err(ndev,
			   "Descriptors of tx and rx must be equal");
		return -EINVAL;
	}

	if (param->tx_pending > HNS3_RING_MAX_PENDING ||
	    param->tx_pending < HNS3_RING_MIN_PENDING) {
		netdev_err(ndev,
			   "Descriptors requested (Tx/Rx: %d) out of range [%d-%d]\n",
			   param->tx_pending, HNS3_RING_MIN_PENDING,
			   HNS3_RING_MAX_PENDING);
		return -EINVAL;
	}

	new_desc_num = param->tx_pending;

	/* Hardware requires that its descriptors must be multiple of eight */
	new_desc_num = ALIGN(new_desc_num, HNS3_RING_BD_MULTIPLE);
	old_desc_num = h->kinfo.num_desc;
	if (old_desc_num == new_desc_num)
		return 0;

	netdev_info(ndev,
		    "Changing descriptor count from %d to %d.\n",
		    old_desc_num, new_desc_num);

	if (if_running)
		dev_close(ndev);

	ret = hns3_uninit_all_ring(priv);
	if (ret)
		return ret;

	ret = hns3_change_all_ring_bd_num(priv, new_desc_num);
	if (ret) {
		ret = hns3_change_all_ring_bd_num(priv, old_desc_num);
		if (ret) {
			netdev_err(ndev,
				   "Revert to old bd num fail, ret=%d.\n", ret);
			return ret;
		}
	}

	if (if_running)
		ret = dev_open(ndev);

	return ret;
}