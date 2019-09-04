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
struct bonding {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** sysfs_groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  bonding_group ; 

void bond_prepare_sysfs_group(struct bonding *bond)
{
	bond->dev->sysfs_groups[0] = &bonding_group;
}