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
struct platform_device {int dummy; } ;
struct net_device {scalar_t__ reg_state; scalar_t__ phydev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * notifier_call; } ;
struct hns_nic_priv {int /*<<< orphan*/  fwnode; int /*<<< orphan*/  service_task; int /*<<< orphan*/  state; TYPE_1__ notifier_block; int /*<<< orphan*/ * ae_handle; int /*<<< orphan*/ * ring_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 scalar_t__ NETREG_UNINITIALIZED ; 
 int /*<<< orphan*/  NIC_STATE_REMOVING ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  hnae_put_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hnae_unregister_notifier (TYPE_1__*) ; 
 int /*<<< orphan*/  hns_nic_uninit_ring_data (struct hns_nic_priv*) ; 
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_disconnect (scalar_t__) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_of_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int hns_nic_dev_remove(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct hns_nic_priv *priv = netdev_priv(ndev);

	if (ndev->reg_state != NETREG_UNINITIALIZED)
		unregister_netdev(ndev);

	if (priv->ring_data)
		hns_nic_uninit_ring_data(priv);
	priv->ring_data = NULL;

	if (ndev->phydev)
		phy_disconnect(ndev->phydev);

	if (!IS_ERR_OR_NULL(priv->ae_handle))
		hnae_put_handle(priv->ae_handle);
	priv->ae_handle = NULL;
	if (priv->notifier_block.notifier_call)
		hnae_unregister_notifier(&priv->notifier_block);
	priv->notifier_block.notifier_call = NULL;

	set_bit(NIC_STATE_REMOVING, &priv->state);
	(void)cancel_work_sync(&priv->service_task);

	/* safe for ACPI FW */
	of_node_put(to_of_node(priv->fwnode));

	free_netdev(ndev);
	return 0;
}