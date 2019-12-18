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
struct TYPE_2__ {int /*<<< orphan*/ * arp_targets; } ;
struct bonding {int /*<<< orphan*/  dev; TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  _bond_options_arp_ip_target_set (struct bonding*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bond_get_targets_ip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bond_is_ip_target_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int _bond_option_arp_ip_target_add(struct bonding *bond, __be32 target)
{
	__be32 *targets = bond->params.arp_targets;
	int ind;

	if (!bond_is_ip_target_ok(target)) {
		netdev_err(bond->dev, "invalid ARP target %pI4 specified for addition\n",
			   &target);
		return -EINVAL;
	}

	if (bond_get_targets_ip(targets, target) != -1) { /* dup */
		netdev_err(bond->dev, "ARP target %pI4 is already present\n",
			   &target);
		return -EINVAL;
	}

	ind = bond_get_targets_ip(targets, 0); /* first free slot */
	if (ind == -1) {
		netdev_err(bond->dev, "ARP target table is full!\n");
		return -EINVAL;
	}

	netdev_dbg(bond->dev, "Adding ARP target %pI4\n", &target);

	_bond_options_arp_ip_target_set(bond, ind, target, jiffies);

	return 0;
}