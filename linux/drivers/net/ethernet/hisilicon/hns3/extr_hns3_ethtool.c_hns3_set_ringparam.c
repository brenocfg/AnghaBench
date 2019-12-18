#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct net_device {TYPE_3__* netdev_ops; } ;
struct hns3_nic_priv {TYPE_1__* ring_data; struct hnae3_handle* ae_handle; } ;
struct hns3_enet_ring {int dummy; } ;
struct TYPE_6__ {size_t num_tqps; } ;
struct hnae3_handle {TYPE_2__ kinfo; } ;
struct ethtool_ringparam {int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_pending; } ;
struct TYPE_8__ {scalar_t__ desc_num; } ;
struct TYPE_7__ {int (* ndo_open ) (struct net_device*) ;int /*<<< orphan*/  (* ndo_stop ) (struct net_device*) ;} ;
struct TYPE_5__ {TYPE_4__* ring; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HNS3_RING_BD_MULTIPLE ; 
 struct hns3_enet_ring* hns3_backup_ringparam (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_change_all_ring_bd_num (struct hns3_nic_priv*,scalar_t__,scalar_t__) ; 
 int hns3_check_ringparam (struct net_device*,struct ethtool_ringparam*) ; 
 int /*<<< orphan*/  hns3_fini_ring (struct hns3_enet_ring*) ; 
 int hns3_init_all_ring (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  kfree (struct hns3_enet_ring*) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,struct hns3_enet_ring*,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int netif_running (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int stub2 (struct net_device*) ; 

__attribute__((used)) static int hns3_set_ringparam(struct net_device *ndev,
			      struct ethtool_ringparam *param)
{
	struct hns3_nic_priv *priv = netdev_priv(ndev);
	struct hnae3_handle *h = priv->ae_handle;
	struct hns3_enet_ring *tmp_rings;
	bool if_running = netif_running(ndev);
	u32 old_tx_desc_num, new_tx_desc_num;
	u32 old_rx_desc_num, new_rx_desc_num;
	u16 queue_num = h->kinfo.num_tqps;
	int ret, i;

	ret = hns3_check_ringparam(ndev, param);
	if (ret)
		return ret;

	/* Hardware requires that its descriptors must be multiple of eight */
	new_tx_desc_num = ALIGN(param->tx_pending, HNS3_RING_BD_MULTIPLE);
	new_rx_desc_num = ALIGN(param->rx_pending, HNS3_RING_BD_MULTIPLE);
	old_tx_desc_num = priv->ring_data[0].ring->desc_num;
	old_rx_desc_num = priv->ring_data[queue_num].ring->desc_num;
	if (old_tx_desc_num == new_tx_desc_num &&
	    old_rx_desc_num == new_rx_desc_num)
		return 0;

	tmp_rings = hns3_backup_ringparam(priv);
	if (!tmp_rings) {
		netdev_err(ndev,
			   "backup ring param failed by allocating memory fail\n");
		return -ENOMEM;
	}

	netdev_info(ndev,
		    "Changing Tx/Rx ring depth from %d/%d to %d/%d\n",
		    old_tx_desc_num, old_rx_desc_num,
		    new_tx_desc_num, new_rx_desc_num);

	if (if_running)
		ndev->netdev_ops->ndo_stop(ndev);

	hns3_change_all_ring_bd_num(priv, new_tx_desc_num, new_rx_desc_num);
	ret = hns3_init_all_ring(priv);
	if (ret) {
		netdev_err(ndev, "Change bd num fail, revert to old value(%d)\n",
			   ret);

		hns3_change_all_ring_bd_num(priv, old_tx_desc_num,
					    old_rx_desc_num);
		for (i = 0; i < h->kinfo.num_tqps * 2; i++)
			memcpy(priv->ring_data[i].ring, &tmp_rings[i],
			       sizeof(struct hns3_enet_ring));
	} else {
		for (i = 0; i < h->kinfo.num_tqps * 2; i++)
			hns3_fini_ring(&tmp_rings[i]);
	}

	kfree(tmp_rings);

	if (if_running)
		ret = ndev->netdev_ops->ndo_open(ndev);

	return ret;
}