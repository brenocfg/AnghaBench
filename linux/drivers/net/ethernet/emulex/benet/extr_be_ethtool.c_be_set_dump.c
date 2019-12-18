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
struct ethtool_dump {int flag; } ;
struct device {int dummy; } ;
struct be_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  LANCER_DELETE_FW_DUMP 129 
#define  LANCER_INITIATE_FW_DUMP 128 
 int /*<<< orphan*/  MAX_PRIVILEGES ; 
 int /*<<< orphan*/  check_privilege (struct be_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  lancer_chip (struct be_adapter*) ; 
 int lancer_delete_dump (struct be_adapter*) ; 
 int lancer_initiate_dump (struct be_adapter*) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int be_set_dump(struct net_device *netdev, struct ethtool_dump *dump)
{
	struct be_adapter *adapter = netdev_priv(netdev);
	struct device *dev = &adapter->pdev->dev;
	int status;

	if (!lancer_chip(adapter) ||
	    !check_privilege(adapter, MAX_PRIVILEGES))
		return -EOPNOTSUPP;

	switch (dump->flag) {
	case LANCER_INITIATE_FW_DUMP:
		status = lancer_initiate_dump(adapter);
		if (!status)
			dev_info(dev, "FW dump initiated successfully\n");
		break;
	case LANCER_DELETE_FW_DUMP:
		status = lancer_delete_dump(adapter);
		if (!status)
			dev_info(dev, "FW dump deleted successfully\n");
	break;
	default:
		dev_err(dev, "Invalid dump level: 0x%x\n", dump->flag);
		return -EINVAL;
	}
	return status;
}