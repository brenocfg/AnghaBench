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
struct ifbond {int /*<<< orphan*/  num_slaves; int /*<<< orphan*/  miimon; int /*<<< orphan*/  bond_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  miimon; } ;
struct bonding {int /*<<< orphan*/  slave_cnt; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOND_MODE (struct bonding*) ; 

__attribute__((used)) static void bond_fill_ifbond(struct bonding *bond, struct ifbond *info)
{
	info->bond_mode = BOND_MODE(bond);
	info->miimon = bond->params.miimon;
	info->num_slaves = bond->slave_cnt;
}