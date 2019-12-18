#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct slave {TYPE_1__* dev; } ;
struct bonding {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_SLAVE ; 
 int /*<<< orphan*/  netdev_upper_dev_unlink (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bond_upper_dev_unlink(struct bonding *bond, struct slave *slave)
{
	netdev_upper_dev_unlink(slave->dev, bond->dev);
	slave->dev->flags &= ~IFF_SLAVE;
}