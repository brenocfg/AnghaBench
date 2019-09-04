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
struct platform_device {TYPE_1__ dev; } ;
struct dfl_feature {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  port_afu_attrs ; 
 int /*<<< orphan*/  sysfs_remove_files (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void port_afu_uinit(struct platform_device *pdev,
			   struct dfl_feature *feature)
{
	dev_dbg(&pdev->dev, "PORT AFU UInit.\n");

	sysfs_remove_files(&pdev->dev.kobj, port_afu_attrs);
}