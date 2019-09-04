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
struct ifbond {int dummy; } ;
struct bonding {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bond_fill_ifbond (struct bonding*,struct ifbond*) ; 
 struct bonding* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void bond_info_query(struct net_device *bond_dev, struct ifbond *info)
{
	struct bonding *bond = netdev_priv(bond_dev);
	bond_fill_ifbond(bond, info);
}