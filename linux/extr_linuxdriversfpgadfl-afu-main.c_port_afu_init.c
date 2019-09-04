#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; struct resource* resource; } ;
struct dfl_feature {size_t resource_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFL_PORT_REGION_INDEX_AFU ; 
 int DFL_PORT_REGION_MMAP ; 
 int DFL_PORT_REGION_READ ; 
 int DFL_PORT_REGION_WRITE ; 
 int afu_mmio_region_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_get_platdata (TYPE_1__*) ; 
 int /*<<< orphan*/  port_afu_attrs ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int sysfs_create_files (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int port_afu_init(struct platform_device *pdev,
			 struct dfl_feature *feature)
{
	struct resource *res = &pdev->resource[feature->resource_index];
	int ret;

	dev_dbg(&pdev->dev, "PORT AFU Init.\n");

	ret = afu_mmio_region_add(dev_get_platdata(&pdev->dev),
				  DFL_PORT_REGION_INDEX_AFU, resource_size(res),
				  res->start, DFL_PORT_REGION_READ |
				  DFL_PORT_REGION_WRITE | DFL_PORT_REGION_MMAP);
	if (ret)
		return ret;

	return sysfs_create_files(&pdev->dev.kobj, port_afu_attrs);
}