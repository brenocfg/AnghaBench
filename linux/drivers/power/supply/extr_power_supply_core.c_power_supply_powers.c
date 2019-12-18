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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct power_supply {TYPE_1__ dev; } ;
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

int power_supply_powers(struct power_supply *psy, struct device *dev)
{
	return sysfs_create_link(&psy->dev.kobj, &dev->kobj, "powers");
}