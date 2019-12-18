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
struct cnic_eth_dev {scalar_t__ drv_state; } ;
struct bnx2x {int cnic_enabled; int /*<<< orphan*/ * cnic_kwq; int /*<<< orphan*/  cnic_mutex; int /*<<< orphan*/  cnic_ops; struct cnic_eth_dev cnic_eth_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static int bnx2x_unregister_cnic(struct net_device *dev)
{
	struct bnx2x *bp = netdev_priv(dev);
	struct cnic_eth_dev *cp = &bp->cnic_eth_dev;

	mutex_lock(&bp->cnic_mutex);
	cp->drv_state = 0;
	RCU_INIT_POINTER(bp->cnic_ops, NULL);
	mutex_unlock(&bp->cnic_mutex);
	synchronize_rcu();
	bp->cnic_enabled = false;
	kfree(bp->cnic_kwq);
	bp->cnic_kwq = NULL;

	return 0;
}