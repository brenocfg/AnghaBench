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
struct net_device {int tx_queue_len; int flags; int needs_free_netdev; int /*<<< orphan*/  mtu; int /*<<< orphan*/  type; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_CAIF ; 
 int /*<<< orphan*/  CFV_DEF_MTU_SIZE ; 
 int IFF_NOARP ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  cfv_netdev_ops ; 

__attribute__((used)) static void cfv_netdev_setup(struct net_device *netdev)
{
	netdev->netdev_ops = &cfv_netdev_ops;
	netdev->type = ARPHRD_CAIF;
	netdev->tx_queue_len = 100;
	netdev->flags = IFF_POINTOPOINT | IFF_NOARP;
	netdev->mtu = CFV_DEF_MTU_SIZE;
	netdev->needs_free_netdev = true;
}