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
struct ab8500_fg {int /*<<< orphan*/  dev; int /*<<< orphan*/  fg_kobject; } ;

/* Variables and functions */
 int /*<<< orphan*/  ab8500_fg_ktype ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int ab8500_fg_sysfs_init(struct ab8500_fg *di)
{
	int ret = 0;

	ret = kobject_init_and_add(&di->fg_kobject,
		&ab8500_fg_ktype,
		NULL, "battery");
	if (ret < 0)
		dev_err(di->dev, "failed to create sysfs entry\n");

	return ret;
}