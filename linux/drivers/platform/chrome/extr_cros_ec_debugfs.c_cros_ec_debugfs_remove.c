#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct cros_ec_dev {TYPE_2__* debug_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  cros_ec_cleanup_console_log (TYPE_2__*) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 struct cros_ec_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cros_ec_debugfs_remove(struct platform_device *pd)
{
	struct cros_ec_dev *ec = dev_get_drvdata(pd->dev.parent);

	debugfs_remove_recursive(ec->debug_info->dir);
	cros_ec_cleanup_console_log(ec->debug_info);

	return 0;
}