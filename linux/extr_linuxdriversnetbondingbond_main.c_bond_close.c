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
struct bonding {int /*<<< orphan*/ * recv_probe; scalar_t__ send_peer_notif; } ;

/* Variables and functions */
 int /*<<< orphan*/  bond_alb_deinitialize (struct bonding*) ; 
 scalar_t__ bond_is_lb (struct bonding*) ; 
 int /*<<< orphan*/  bond_work_cancel_all (struct bonding*) ; 
 struct bonding* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bond_close(struct net_device *bond_dev)
{
	struct bonding *bond = netdev_priv(bond_dev);

	bond_work_cancel_all(bond);
	bond->send_peer_notif = 0;
	if (bond_is_lb(bond))
		bond_alb_deinitialize(bond);
	bond->recv_probe = NULL;

	return 0;
}