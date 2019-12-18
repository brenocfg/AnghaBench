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
typedef  int /*<<< orphan*/  u8 ;
struct bonding {int /*<<< orphan*/  dev; } ;
struct bond_opt_value {char* string; scalar_t__ value; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int EPERM ; 
 int bond_option_arp_ip_target_add (struct bonding*,scalar_t__) ; 
 int bond_option_arp_ip_target_rem (struct bonding*,scalar_t__) ; 
 int /*<<< orphan*/  in4_pton (char*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int bond_option_arp_ip_targets_set(struct bonding *bond,
					  const struct bond_opt_value *newval)
{
	int ret = -EPERM;
	__be32 target;

	if (newval->string) {
		if (!in4_pton(newval->string+1, -1, (u8 *)&target, -1, NULL)) {
			netdev_err(bond->dev, "invalid ARP target %pI4 specified\n",
				   &target);
			return ret;
		}
		if (newval->string[0] == '+')
			ret = bond_option_arp_ip_target_add(bond, target);
		else if (newval->string[0] == '-')
			ret = bond_option_arp_ip_target_rem(bond, target);
		else
			netdev_err(bond->dev, "no command found in arp_ip_targets file - use +<addr> or -<addr>\n");
	} else {
		target = newval->value;
		ret = bond_option_arp_ip_target_add(bond, target);
	}

	return ret;
}