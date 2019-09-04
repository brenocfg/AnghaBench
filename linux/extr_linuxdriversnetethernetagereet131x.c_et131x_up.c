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
struct net_device {int /*<<< orphan*/  phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  et131x_enable_txrx (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void et131x_up(struct net_device *netdev)
{
	et131x_enable_txrx(netdev);
	phy_start(netdev->phydev);
}