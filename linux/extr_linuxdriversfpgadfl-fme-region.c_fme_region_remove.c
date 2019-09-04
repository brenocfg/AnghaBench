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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct fpga_region {struct fpga_manager* mgr; } ;
struct fpga_manager {int dummy; } ;

/* Variables and functions */
 struct fpga_region* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fpga_mgr_put (struct fpga_manager*) ; 
 int /*<<< orphan*/  fpga_region_unregister (struct fpga_region*) ; 

__attribute__((used)) static int fme_region_remove(struct platform_device *pdev)
{
	struct fpga_region *region = dev_get_drvdata(&pdev->dev);
	struct fpga_manager *mgr = region->mgr;

	fpga_region_unregister(region);
	fpga_mgr_put(mgr);

	return 0;
}