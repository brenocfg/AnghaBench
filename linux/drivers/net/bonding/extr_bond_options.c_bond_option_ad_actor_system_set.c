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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  ad_actor_system; } ;
struct bonding {int /*<<< orphan*/  dev; TYPE_1__ params; } ;
struct bond_opt_value {int /*<<< orphan*/  value; scalar_t__ string; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  bond_3ad_update_ad_actor_settings (struct bonding*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mac_pton (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int bond_option_ad_actor_system_set(struct bonding *bond,
					   const struct bond_opt_value *newval)
{
	u8 macaddr[ETH_ALEN];
	u8 *mac;

	if (newval->string) {
		if (!mac_pton(newval->string, macaddr))
			goto err;
		mac = macaddr;
	} else {
		mac = (u8 *)&newval->value;
	}

	if (!is_valid_ether_addr(mac))
		goto err;

	netdev_dbg(bond->dev, "Setting ad_actor_system to %pM\n", mac);
	ether_addr_copy(bond->params.ad_actor_system, mac);
	bond_3ad_update_ad_actor_settings(bond);

	return 0;

err:
	netdev_err(bond->dev, "Invalid ad_actor_system MAC address.\n");
	return -EINVAL;
}