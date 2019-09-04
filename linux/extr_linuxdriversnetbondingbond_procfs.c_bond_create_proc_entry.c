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
struct net_device {int /*<<< orphan*/  name; } ;
struct bonding {int /*<<< orphan*/  proc_file_name; int /*<<< orphan*/ * proc_entry; struct net_device* dev; } ;
struct bond_net {scalar_t__ proc_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  bond_info_seq_ops ; 
 int /*<<< orphan*/  bond_net_id ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bond_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * proc_create_seq_data (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ *,struct bonding*) ; 

void bond_create_proc_entry(struct bonding *bond)
{
	struct net_device *bond_dev = bond->dev;
	struct bond_net *bn = net_generic(dev_net(bond_dev), bond_net_id);

	if (bn->proc_dir) {
		bond->proc_entry = proc_create_seq_data(bond_dev->name, 0444,
				bn->proc_dir, &bond_info_seq_ops, bond);
		if (bond->proc_entry == NULL)
			netdev_warn(bond_dev, "Cannot create /proc/net/%s/%s\n",
				    DRV_NAME, bond_dev->name);
		else
			memcpy(bond->proc_file_name, bond_dev->name, IFNAMSIZ);
	}
}