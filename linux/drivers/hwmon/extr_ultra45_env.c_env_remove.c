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
struct platform_device {int /*<<< orphan*/ * resource; TYPE_1__ dev; } ;
struct env {int /*<<< orphan*/  regs; int /*<<< orphan*/  hwmon_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SIZE ; 
 int /*<<< orphan*/  env_group ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct env* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int env_remove(struct platform_device *op)
{
	struct env *p = platform_get_drvdata(op);

	if (p) {
		sysfs_remove_group(&op->dev.kobj, &env_group);
		hwmon_device_unregister(p->hwmon_dev);
		of_iounmap(&op->resource[0], p->regs, REG_SIZE);
	}

	return 0;
}