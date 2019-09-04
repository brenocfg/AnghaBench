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
 int /*<<< orphan*/  port_hdr_attrs ; 
 int /*<<< orphan*/  port_reset (struct platform_device*) ; 
 int sysfs_create_files (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int port_hdr_init(struct platform_device *pdev,
			 struct dfl_feature *feature)
{
	dev_dbg(&pdev->dev, "PORT HDR Init.\n");

	port_reset(pdev);

	return sysfs_create_files(&pdev->dev.kobj, port_hdr_attrs);
}