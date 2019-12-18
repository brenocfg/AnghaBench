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
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  perm_addr; } ;
struct bnad {int /*<<< orphan*/  perm_addr; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnad_set_netdev_perm_addr(struct bnad *bnad)
{
	struct net_device *netdev = bnad->netdev;

	ether_addr_copy(netdev->perm_addr, bnad->perm_addr);
	if (is_zero_ether_addr(netdev->dev_addr))
		ether_addr_copy(netdev->dev_addr, bnad->perm_addr);
}