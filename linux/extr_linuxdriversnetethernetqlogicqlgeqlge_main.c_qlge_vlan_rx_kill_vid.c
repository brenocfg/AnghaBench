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
typedef  int /*<<< orphan*/  u16 ;
struct ql_adapter {int /*<<< orphan*/  active_vlans; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  SEM_MAC_ADDR_MASK ; 
 int __qlge_vlan_rx_kill_vid (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ql_adapter* netdev_priv (struct net_device*) ; 
 int ql_sem_spinlock (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_sem_unlock (struct ql_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qlge_vlan_rx_kill_vid(struct net_device *ndev, __be16 proto, u16 vid)
{
	struct ql_adapter *qdev = netdev_priv(ndev);
	int status;
	int err;

	status = ql_sem_spinlock(qdev, SEM_MAC_ADDR_MASK);
	if (status)
		return status;

	err = __qlge_vlan_rx_kill_vid(qdev, vid);
	clear_bit(vid, qdev->active_vlans);

	ql_sem_unlock(qdev, SEM_MAC_ADDR_MASK);

	return err;
}