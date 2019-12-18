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
struct omap_iommu {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  omap2_iommu_dump_ctx (struct omap_iommu*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t omap_iommu_dump_ctx(struct omap_iommu *obj, char *buf,
				   ssize_t bytes)
{
	if (!obj || !buf)
		return -EINVAL;

	pm_runtime_get_sync(obj->dev);

	bytes = omap2_iommu_dump_ctx(obj, buf, bytes);

	pm_runtime_put_sync(obj->dev);

	return bytes;
}