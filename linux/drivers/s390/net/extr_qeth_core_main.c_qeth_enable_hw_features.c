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
struct qeth_card {TYPE_1__* gdev; } ;
struct net_device {int /*<<< orphan*/  features; int /*<<< orphan*/  wanted_features; int /*<<< orphan*/  hw_features; struct qeth_card* ml_priv; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_LAYER2 (struct qeth_card*) ; 
 scalar_t__ IS_VM_NIC (struct qeth_card*) ; 
 int /*<<< orphan*/  NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  netdev_update_features (struct net_device*) ; 

void qeth_enable_hw_features(struct net_device *dev)
{
	struct qeth_card *card = dev->ml_priv;
	netdev_features_t features;

	features = dev->features;
	/* force-off any feature that might need an IPA sequence.
	 * netdev_update_features() will restart them.
	 */
	dev->features &= ~dev->hw_features;
	/* toggle VLAN filter, so that VIDs are re-programmed: */
	if (IS_LAYER2(card) && IS_VM_NIC(card)) {
		dev->features &= ~NETIF_F_HW_VLAN_CTAG_FILTER;
		dev->wanted_features |= NETIF_F_HW_VLAN_CTAG_FILTER;
	}
	netdev_update_features(dev);
	if (features != dev->features)
		dev_warn(&card->gdev->dev,
			 "Device recovery failed to restore all offload features\n");
}