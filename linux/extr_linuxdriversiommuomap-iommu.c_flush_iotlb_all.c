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
struct iotlb_lock {scalar_t__ vict; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_GFLUSH ; 
 int /*<<< orphan*/  iommu_write_reg (struct omap_iommu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iotlb_lock_set (struct omap_iommu*,struct iotlb_lock*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flush_iotlb_all(struct omap_iommu *obj)
{
	struct iotlb_lock l;

	pm_runtime_get_sync(obj->dev);

	l.base = 0;
	l.vict = 0;
	iotlb_lock_set(obj, &l);

	iommu_write_reg(obj, 1, MMU_GFLUSH);

	pm_runtime_put_sync(obj->dev);
}