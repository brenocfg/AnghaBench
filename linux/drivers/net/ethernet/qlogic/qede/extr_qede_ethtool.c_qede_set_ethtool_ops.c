#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qede_dev {int dummy; } ;
struct net_device {int /*<<< orphan*/ * ethtool_ops; } ;

/* Variables and functions */
 scalar_t__ IS_VF (struct qede_dev*) ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qede_ethtool_ops ; 
 int /*<<< orphan*/  qede_vf_ethtool_ops ; 

void qede_set_ethtool_ops(struct net_device *dev)
{
	struct qede_dev *edev = netdev_priv(dev);

	if (IS_VF(edev))
		dev->ethtool_ops = &qede_vf_ethtool_ops;
	else
		dev->ethtool_ops = &qede_ethtool_ops;
}