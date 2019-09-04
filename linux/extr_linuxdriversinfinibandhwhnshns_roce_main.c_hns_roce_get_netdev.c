#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct net_device {int dummy; } ;
struct ib_device {int dummy; } ;
struct TYPE_4__ {struct net_device** netdevs; } ;
struct TYPE_3__ {int num_ports; } ;
struct hns_roce_dev {TYPE_2__ iboe; TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct hns_roce_dev* to_hr_dev (struct ib_device*) ; 

__attribute__((used)) static struct net_device *hns_roce_get_netdev(struct ib_device *ib_dev,
					      u8 port_num)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ib_dev);
	struct net_device *ndev;

	if (port_num < 1 || port_num > hr_dev->caps.num_ports)
		return NULL;

	rcu_read_lock();

	ndev = hr_dev->iboe.netdevs[port_num - 1];
	if (ndev)
		dev_hold(ndev);

	rcu_read_unlock();
	return ndev;
}