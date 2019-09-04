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
typedef  int u8 ;
struct pvrdma_dev {struct net_device* netdev; } ;
struct net_device {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct pvrdma_dev* to_vdev (struct ib_device*) ; 

__attribute__((used)) static struct net_device *pvrdma_get_netdev(struct ib_device *ibdev,
					    u8 port_num)
{
	struct net_device *netdev;
	struct pvrdma_dev *dev = to_vdev(ibdev);

	if (port_num != 1)
		return NULL;

	rcu_read_lock();
	netdev = dev->netdev;
	if (netdev)
		dev_hold(netdev);
	rcu_read_unlock();

	return netdev;
}