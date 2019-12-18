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
struct bonding {int /*<<< orphan*/  slave_arr_work; int /*<<< orphan*/  ad_work; int /*<<< orphan*/  arp_work; int /*<<< orphan*/  mii_work; int /*<<< orphan*/  alb_work; int /*<<< orphan*/  mcast_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bond_3ad_state_machine_handler ; 
 int /*<<< orphan*/  bond_alb_monitor ; 
 int /*<<< orphan*/  bond_arp_monitor ; 
 int /*<<< orphan*/  bond_mii_monitor ; 
 int /*<<< orphan*/  bond_resend_igmp_join_requests_delayed ; 
 int /*<<< orphan*/  bond_slave_arr_handler ; 

void bond_work_init_all(struct bonding *bond)
{
	INIT_DELAYED_WORK(&bond->mcast_work,
			  bond_resend_igmp_join_requests_delayed);
	INIT_DELAYED_WORK(&bond->alb_work, bond_alb_monitor);
	INIT_DELAYED_WORK(&bond->mii_work, bond_mii_monitor);
	INIT_DELAYED_WORK(&bond->arp_work, bond_arp_monitor);
	INIT_DELAYED_WORK(&bond->ad_work, bond_3ad_state_machine_handler);
	INIT_DELAYED_WORK(&bond->slave_arr_work, bond_slave_arr_handler);
}