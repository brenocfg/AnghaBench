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
struct enic {int /*<<< orphan*/  tx_hang_reset; } ;

/* Variables and functions */
 struct enic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void enic_tx_timeout(struct net_device *netdev)
{
	struct enic *enic = netdev_priv(netdev);
	schedule_work(&enic->tx_hang_reset);
}