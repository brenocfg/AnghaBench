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
struct TYPE_2__ {int tlb_dynamic_lb; scalar_t__ mode; int /*<<< orphan*/  arp_validate; scalar_t__ miimon; scalar_t__ arp_interval; } ;
struct bonding {TYPE_1__ params; int /*<<< orphan*/  dev; } ;
struct bond_opt_value {scalar_t__ value; scalar_t__ string; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOND_ARP_VALIDATE_NONE ; 
 scalar_t__ BOND_DEFAULT_MIIMON ; 
 scalar_t__ BOND_MODE_ALB ; 
 int /*<<< orphan*/  bond_mode_uses_arp (scalar_t__) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int bond_option_mode_set(struct bonding *bond,
				const struct bond_opt_value *newval)
{
	if (!bond_mode_uses_arp(newval->value)) {
		if (bond->params.arp_interval) {
			netdev_dbg(bond->dev, "%s mode is incompatible with arp monitoring, start mii monitoring\n",
				   newval->string);
			/* disable arp monitoring */
			bond->params.arp_interval = 0;
		}

		if (!bond->params.miimon) {
			/* set miimon to default value */
			bond->params.miimon = BOND_DEFAULT_MIIMON;
			netdev_dbg(bond->dev, "Setting MII monitoring interval to %d\n",
				   bond->params.miimon);
		}
	}

	if (newval->value == BOND_MODE_ALB)
		bond->params.tlb_dynamic_lb = 1;

	/* don't cache arp_validate between modes */
	bond->params.arp_validate = BOND_ARP_VALIDATE_NONE;
	bond->params.mode = newval->value;

	return 0;
}