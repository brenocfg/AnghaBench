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
struct net_device {int dummy; } ;
struct ibmvnic_adapter {scalar_t__ state; int /*<<< orphan*/  tasklet; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ VNIC_OPEN ; 
 struct net_device* dev_get_drvdata (struct device*) ; 
 struct ibmvnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ibmvnic_resume(struct device *dev)
{
	struct net_device *netdev = dev_get_drvdata(dev);
	struct ibmvnic_adapter *adapter = netdev_priv(netdev);

	if (adapter->state != VNIC_OPEN)
		return 0;

	tasklet_schedule(&adapter->tasklet);

	return 0;
}