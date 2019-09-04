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
struct bonding {int /*<<< orphan*/  slave_arr_work; int /*<<< orphan*/  mcast_work; int /*<<< orphan*/  ad_work; int /*<<< orphan*/  alb_work; int /*<<< orphan*/  arp_work; int /*<<< orphan*/  mii_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bond_work_cancel_all(struct bonding *bond)
{
	cancel_delayed_work_sync(&bond->mii_work);
	cancel_delayed_work_sync(&bond->arp_work);
	cancel_delayed_work_sync(&bond->alb_work);
	cancel_delayed_work_sync(&bond->ad_work);
	cancel_delayed_work_sync(&bond->mcast_work);
	cancel_delayed_work_sync(&bond->slave_arr_work);
}