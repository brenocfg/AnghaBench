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
struct usb_interface {int dummy; } ;
struct lan78xx_priv {int /*<<< orphan*/  set_vlan; int /*<<< orphan*/  set_multicast; int /*<<< orphan*/  wol; scalar_t__* vlan_table; int /*<<< orphan*/  dataport_mutex; int /*<<< orphan*/  rfe_ctl_lock; struct lan78xx_net* dev; } ;
struct lan78xx_net {unsigned long* data; TYPE_1__* net; scalar_t__ hard_mtu; } ;
struct TYPE_2__ {int features; int hw_features; int /*<<< orphan*/  flags; scalar_t__ hard_header_len; scalar_t__ mtu; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_RX_CSUM_ENABLE ; 
 scalar_t__ DEFAULT_TSO_CSUM_ENABLE ; 
 scalar_t__ DEFAULT_TX_CSUM_ENABLE ; 
 scalar_t__ DEFAULT_VLAN_FILTER_ENABLE ; 
 scalar_t__ DEFAULT_VLAN_RX_OFFLOAD ; 
 int DP_SEL_VHF_VLAN_LEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IFF_MULTICAST ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 scalar_t__ TX_OVERHEAD ; 
 int /*<<< orphan*/  WAKE_MAGIC ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct lan78xx_priv*) ; 
 scalar_t__ kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan78xx_deferred_multicast_write ; 
 int /*<<< orphan*/  lan78xx_deferred_vlan_write ; 
 int lan78xx_get_endpoints (struct lan78xx_net*,struct usb_interface*) ; 
 int lan78xx_mdio_init (struct lan78xx_net*) ; 
 int /*<<< orphan*/  lan78xx_remove_irq_domain (struct lan78xx_net*) ; 
 int lan78xx_reset (struct lan78xx_net*) ; 
 int lan78xx_setup_irq_domain (struct lan78xx_net*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_warn (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lan78xx_bind(struct lan78xx_net *dev, struct usb_interface *intf)
{
	struct lan78xx_priv *pdata = NULL;
	int ret;
	int i;

	ret = lan78xx_get_endpoints(dev, intf);
	if (ret) {
		netdev_warn(dev->net, "lan78xx_get_endpoints failed: %d\n",
			    ret);
		return ret;
	}

	dev->data[0] = (unsigned long)kzalloc(sizeof(*pdata), GFP_KERNEL);

	pdata = (struct lan78xx_priv *)(dev->data[0]);
	if (!pdata) {
		netdev_warn(dev->net, "Unable to allocate lan78xx_priv");
		return -ENOMEM;
	}

	pdata->dev = dev;

	spin_lock_init(&pdata->rfe_ctl_lock);
	mutex_init(&pdata->dataport_mutex);

	INIT_WORK(&pdata->set_multicast, lan78xx_deferred_multicast_write);

	for (i = 0; i < DP_SEL_VHF_VLAN_LEN; i++)
		pdata->vlan_table[i] = 0;

	INIT_WORK(&pdata->set_vlan, lan78xx_deferred_vlan_write);

	dev->net->features = 0;

	if (DEFAULT_TX_CSUM_ENABLE)
		dev->net->features |= NETIF_F_HW_CSUM;

	if (DEFAULT_RX_CSUM_ENABLE)
		dev->net->features |= NETIF_F_RXCSUM;

	if (DEFAULT_TSO_CSUM_ENABLE)
		dev->net->features |= NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_SG;

	if (DEFAULT_VLAN_RX_OFFLOAD)
		dev->net->features |= NETIF_F_HW_VLAN_CTAG_RX;

	if (DEFAULT_VLAN_FILTER_ENABLE)
		dev->net->features |= NETIF_F_HW_VLAN_CTAG_FILTER;

	dev->net->hw_features = dev->net->features;

	ret = lan78xx_setup_irq_domain(dev);
	if (ret < 0) {
		netdev_warn(dev->net,
			    "lan78xx_setup_irq_domain() failed : %d", ret);
		goto out1;
	}

	dev->net->hard_header_len += TX_OVERHEAD;
	dev->hard_mtu = dev->net->mtu + dev->net->hard_header_len;

	/* Init all registers */
	ret = lan78xx_reset(dev);
	if (ret) {
		netdev_warn(dev->net, "Registers INIT FAILED....");
		goto out2;
	}

	ret = lan78xx_mdio_init(dev);
	if (ret) {
		netdev_warn(dev->net, "MDIO INIT FAILED.....");
		goto out2;
	}

	dev->net->flags |= IFF_MULTICAST;

	pdata->wol = WAKE_MAGIC;

	return ret;

out2:
	lan78xx_remove_irq_domain(dev);

out1:
	netdev_warn(dev->net, "Bind routine FAILED");
	cancel_work_sync(&pdata->set_multicast);
	cancel_work_sync(&pdata->set_vlan);
	kfree(pdata);
	return ret;
}