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
struct hinic_dev {TYPE_1__* netdev; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;
struct TYPE_2__ {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 struct hinic_dev* netdev_priv (struct net_device*) ; 
 int set_features (struct hinic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hinic_set_features(struct net_device *netdev,
			      netdev_features_t features)
{
	struct hinic_dev *nic_dev = netdev_priv(netdev);

	return set_features(nic_dev, nic_dev->netdev->features,
			    features, false);
}