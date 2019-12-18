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
struct slave {int /*<<< orphan*/  link_failure_count; int /*<<< orphan*/  link; TYPE_1__* dev; } ;
struct ifslave {int /*<<< orphan*/  link_failure_count; int /*<<< orphan*/  state; int /*<<< orphan*/  link; int /*<<< orphan*/  slave_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bond_slave_state (struct slave*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bond_fill_ifslave(struct slave *slave, struct ifslave *info)
{
	strcpy(info->slave_name, slave->dev->name);
	info->link = slave->link;
	info->state = bond_slave_state(slave);
	info->link_failure_count = slave->link_failure_count;
}