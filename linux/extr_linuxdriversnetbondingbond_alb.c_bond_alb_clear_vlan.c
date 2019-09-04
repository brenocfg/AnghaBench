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
struct TYPE_2__ {scalar_t__ rlb_enabled; } ;
struct bonding {TYPE_1__ alb_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  rlb_clear_vlan (struct bonding*,unsigned short) ; 

void bond_alb_clear_vlan(struct bonding *bond, unsigned short vlan_id)
{
	if (bond->alb_info.rlb_enabled)
		rlb_clear_vlan(bond, vlan_id);
}