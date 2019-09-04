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
struct hns_nic_priv {struct hnae_handle* ae_handle; int /*<<< orphan*/ * ring_data; int /*<<< orphan*/  dev; int /*<<< orphan*/  port_id; int /*<<< orphan*/  fwnode; TYPE_1__* netdev; } ;
struct hnae_handle {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR_OR_NULL (struct hnae_handle*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct hnae_handle* hnae_get_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hnae_put_handle (struct hnae_handle*) ; 
 int hns_nic_init_phy (struct net_device*,struct hnae_handle*) ; 
 int hns_nic_init_ring_data (struct hns_nic_priv*) ; 
 int /*<<< orphan*/  hns_nic_set_priv_ops (struct net_device*) ; 
 int /*<<< orphan*/  hns_nic_uninit_ring_data (struct hns_nic_priv*) ; 
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 
 int register_netdev (struct net_device*) ; 

__attribute__((used)) static int hns_nic_try_get_ae(struct net_device *ndev)
{
	struct hns_nic_priv *priv = netdev_priv(ndev);
	struct hnae_handle *h;
	int ret;

	h = hnae_get_handle(&priv->netdev->dev,
			    priv->fwnode, priv->port_id, NULL);
	if (IS_ERR_OR_NULL(h)) {
		ret = -ENODEV;
		dev_dbg(priv->dev, "has not handle, register notifier!\n");
		goto out;
	}
	priv->ae_handle = h;

	ret = hns_nic_init_phy(ndev, h);
	if (ret) {
		dev_err(priv->dev, "probe phy device fail!\n");
		goto out_init_phy;
	}

	ret = hns_nic_init_ring_data(priv);
	if (ret) {
		ret = -ENOMEM;
		goto out_init_ring_data;
	}

	hns_nic_set_priv_ops(ndev);

	ret = register_netdev(ndev);
	if (ret) {
		dev_err(priv->dev, "probe register netdev fail!\n");
		goto out_reg_ndev_fail;
	}
	return 0;

out_reg_ndev_fail:
	hns_nic_uninit_ring_data(priv);
	priv->ring_data = NULL;
out_init_phy:
out_init_ring_data:
	hnae_put_handle(priv->ae_handle);
	priv->ae_handle = NULL;
out:
	return ret;
}