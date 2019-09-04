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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {struct net_device* netdev; } ;
struct ocrdma_dev {TYPE_1__ nic_info; } ;
struct net_device {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct ocrdma_dev* get_ocrdma_dev (struct ib_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct net_device *ocrdma_get_netdev(struct ib_device *ibdev, u8 port_num)
{
	struct ocrdma_dev *dev;
	struct net_device *ndev = NULL;

	rcu_read_lock();

	dev = get_ocrdma_dev(ibdev);
	if (dev)
		ndev = dev->nic_info.netdev;
	if (ndev)
		dev_hold(ndev);

	rcu_read_unlock();

	return ndev;
}