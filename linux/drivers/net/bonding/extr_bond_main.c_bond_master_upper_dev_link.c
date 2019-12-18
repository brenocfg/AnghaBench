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
struct slave {int /*<<< orphan*/  dev; } ;
struct netlink_ext_ack {int dummy; } ;
struct netdev_lag_upper_info {int tx_type; int /*<<< orphan*/  hash_type; } ;
struct bonding {int /*<<< orphan*/  dev; } ;
typedef  enum netdev_lag_tx_type { ____Placeholder_netdev_lag_tx_type } netdev_lag_tx_type ;

/* Variables and functions */
 int /*<<< orphan*/  bond_lag_hash_type (struct bonding*,int) ; 
 int bond_lag_tx_type (struct bonding*) ; 
 int netdev_master_upper_dev_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct slave*,struct netdev_lag_upper_info*,struct netlink_ext_ack*) ; 

__attribute__((used)) static int bond_master_upper_dev_link(struct bonding *bond, struct slave *slave,
				      struct netlink_ext_ack *extack)
{
	struct netdev_lag_upper_info lag_upper_info;
	enum netdev_lag_tx_type type;

	type = bond_lag_tx_type(bond);
	lag_upper_info.tx_type = type;
	lag_upper_info.hash_type = bond_lag_hash_type(bond, type);

	return netdev_master_upper_dev_link(slave->dev, bond->dev, slave,
					    &lag_upper_info, extack);
}