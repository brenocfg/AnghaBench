#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ arp_validate; scalar_t__ arp_interval; } ;
struct bonding {TYPE_1__ params; int /*<<< orphan*/ * recv_probe; TYPE_2__* dev; } ;
struct bond_opt_value {scalar_t__ value; int /*<<< orphan*/  string; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/ * bond_arp_rcv ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_2__*,char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int bond_option_arp_validate_set(struct bonding *bond,
					const struct bond_opt_value *newval)
{
	netdev_dbg(bond->dev, "Setting arp_validate to %s (%llu)\n",
		   newval->string, newval->value);

	if (bond->dev->flags & IFF_UP) {
		if (!newval->value)
			bond->recv_probe = NULL;
		else if (bond->params.arp_interval)
			bond->recv_probe = bond_arp_rcv;
	}
	bond->params.arp_validate = newval->value;

	return 0;
}