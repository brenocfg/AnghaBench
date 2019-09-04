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
struct slave {int dummy; } ;
struct bonding {int dummy; } ;

/* Variables and functions */
 int BOND_MODE (struct bonding*) ; 
#define  BOND_MODE_8023AD 131 
#define  BOND_MODE_ALB 130 
#define  BOND_MODE_TLB 129 
#define  BOND_MODE_XOR 128 
 int /*<<< orphan*/  bond_3ad_handle_link_change (struct slave*,char) ; 
 int /*<<< orphan*/  bond_alb_handle_link_change (struct bonding*,struct slave*,char) ; 
 int /*<<< orphan*/  bond_update_slave_arr (struct bonding*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bond_miimon_link_change(struct bonding *bond,
				    struct slave *slave,
				    char link)
{
	switch (BOND_MODE(bond)) {
	case BOND_MODE_8023AD:
		bond_3ad_handle_link_change(slave, link);
		break;
	case BOND_MODE_TLB:
	case BOND_MODE_ALB:
		bond_alb_handle_link_change(bond, slave, link);
		break;
	case BOND_MODE_XOR:
		bond_update_slave_arr(bond, NULL);
		break;
	}
}