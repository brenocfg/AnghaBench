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
struct net_device {int mtu; } ;
struct cas {int phy_type; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  reset_task_pending; int /*<<< orphan*/  reset_task_pending_mtu; int /*<<< orphan*/  reset_task_pending_all; } ;

/* Variables and functions */
 int CAS_PHY_SERDES ; 
 int /*<<< orphan*/  CAS_RESET_ALL ; 
 int /*<<< orphan*/  CAS_RESET_MTU ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 struct cas* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cas_change_mtu(struct net_device *dev, int new_mtu)
{
	struct cas *cp = netdev_priv(dev);

	dev->mtu = new_mtu;
	if (!netif_running(dev) || !netif_device_present(dev))
		return 0;

	/* let the reset task handle it */
#if 1
	atomic_inc(&cp->reset_task_pending);
	if ((cp->phy_type & CAS_PHY_SERDES)) {
		atomic_inc(&cp->reset_task_pending_all);
	} else {
		atomic_inc(&cp->reset_task_pending_mtu);
	}
	schedule_work(&cp->reset_task);
#else
	atomic_set(&cp->reset_task_pending, (cp->phy_type & CAS_PHY_SERDES) ?
		   CAS_RESET_ALL : CAS_RESET_MTU);
	pr_err("reset called in cas_change_mtu\n");
	schedule_work(&cp->reset_task);
#endif

	flush_work(&cp->reset_task);
	return 0;
}