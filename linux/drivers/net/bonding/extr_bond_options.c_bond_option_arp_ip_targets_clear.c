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
struct bonding {int dummy; } ;

/* Variables and functions */
 int BOND_MAX_ARP_TARGETS ; 
 int /*<<< orphan*/  _bond_options_arp_ip_target_set (struct bonding*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bond_option_arp_ip_targets_clear(struct bonding *bond)
{
	int i;

	for (i = 0; i < BOND_MAX_ARP_TARGETS; i++)
		_bond_options_arp_ip_target_set(bond, i, 0, 0);
}