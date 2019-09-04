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
struct qedr_dev {struct net_device* ndev; } ;
struct net_device {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct qedr_dev* get_qedr_dev (struct ib_device*) ; 

__attribute__((used)) static struct net_device *qedr_get_netdev(struct ib_device *dev, u8 port_num)
{
	struct qedr_dev *qdev;

	qdev = get_qedr_dev(dev);
	dev_hold(qdev->ndev);

	/* The HW vendor's device driver must guarantee
	 * that this function returns NULL before the net device has finished
	 * NETDEV_UNREGISTER state.
	 */
	return qdev->ndev;
}