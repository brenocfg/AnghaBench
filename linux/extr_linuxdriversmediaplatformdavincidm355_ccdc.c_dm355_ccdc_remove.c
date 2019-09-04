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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 TYPE_1__ ccdc_cfg ; 
 int /*<<< orphan*/  ccdc_hw_dev ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  vpfe_unregister_ccdc_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dm355_ccdc_remove(struct platform_device *pdev)
{
	struct resource	*res;

	iounmap(ccdc_cfg.base_addr);
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res)
		release_mem_region(res->start, resource_size(res));
	vpfe_unregister_ccdc_device(&ccdc_hw_dev);
	return 0;
}