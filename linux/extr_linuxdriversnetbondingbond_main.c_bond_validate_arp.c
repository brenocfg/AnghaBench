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
struct slave {void** target_last_arp_rx; void* last_rx; } ;
struct TYPE_2__ {int /*<<< orphan*/  arp_targets; } ;
struct bonding {int /*<<< orphan*/  dev; TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int bond_get_targets_ip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bond_has_this_ip (struct bonding*,int /*<<< orphan*/ ) ; 
 void* jiffies ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,...) ; 

__attribute__((used)) static void bond_validate_arp(struct bonding *bond, struct slave *slave, __be32 sip, __be32 tip)
{
	int i;

	if (!sip || !bond_has_this_ip(bond, tip)) {
		netdev_dbg(bond->dev, "bva: sip %pI4 tip %pI4 not found\n",
			   &sip, &tip);
		return;
	}

	i = bond_get_targets_ip(bond->params.arp_targets, sip);
	if (i == -1) {
		netdev_dbg(bond->dev, "bva: sip %pI4 not found in targets\n",
			   &sip);
		return;
	}
	slave->last_rx = jiffies;
	slave->target_last_arp_rx[i] = jiffies;
}