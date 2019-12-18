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
typedef  int u16 ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {char* name; } ;
struct bonding {int dummy; } ;
struct bond_opt_value {int dummy; } ;
typedef  int /*<<< orphan*/  queue_id_str ;

/* Variables and functions */
 int /*<<< orphan*/  BOND_OPT_QUEUE_ID ; 
 size_t IFLA_BOND_SLAVE_QUEUE_ID ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int __bond_opt_set (struct bonding*,int /*<<< orphan*/ ,struct bond_opt_value*) ; 
 int /*<<< orphan*/  bond_opt_initstr (struct bond_opt_value*,char*) ; 
 struct bonding* netdev_priv (struct net_device*) ; 
 int nla_get_u16 (struct nlattr*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 

__attribute__((used)) static int bond_slave_changelink(struct net_device *bond_dev,
				 struct net_device *slave_dev,
				 struct nlattr *tb[], struct nlattr *data[],
				 struct netlink_ext_ack *extack)
{
	struct bonding *bond = netdev_priv(bond_dev);
	struct bond_opt_value newval;
	int err;

	if (!data)
		return 0;

	if (data[IFLA_BOND_SLAVE_QUEUE_ID]) {
		u16 queue_id = nla_get_u16(data[IFLA_BOND_SLAVE_QUEUE_ID]);
		char queue_id_str[IFNAMSIZ + 7];

		/* queue_id option setting expects slave_name:queue_id */
		snprintf(queue_id_str, sizeof(queue_id_str), "%s:%u\n",
			 slave_dev->name, queue_id);
		bond_opt_initstr(&newval, queue_id_str);
		err = __bond_opt_set(bond, BOND_OPT_QUEUE_ID, &newval);
		if (err)
			return err;
	}

	return 0;
}