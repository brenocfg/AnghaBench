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

/* Variables and functions */
 int __bond_release_one (struct net_device*,struct net_device*,int,int) ; 

int bond_release(struct net_device *bond_dev, struct net_device *slave_dev)
{
	return __bond_release_one(bond_dev, slave_dev, false, false);
}