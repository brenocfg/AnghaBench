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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct ib_device {int dummy; } ;
struct bnxt_re_dev {struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct bnxt_re_dev* to_bnxt_re_dev (struct ib_device*,struct ib_device*) ; 

struct net_device *bnxt_re_get_netdev(struct ib_device *ibdev, u8 port_num)
{
	struct bnxt_re_dev *rdev = to_bnxt_re_dev(ibdev, ibdev);
	struct net_device *netdev = NULL;

	rcu_read_lock();
	if (rdev)
		netdev = rdev->netdev;
	if (netdev)
		dev_hold(netdev);

	rcu_read_unlock();
	return netdev;
}