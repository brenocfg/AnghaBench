#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct v3d_dev {int /*<<< orphan*/  dev; scalar_t__* pt; } ;
struct TYPE_6__ {size_t start; } ;
struct TYPE_4__ {size_t size; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct v3d_bo {TYPE_3__ node; TYPE_2__ base; } ;

/* Variables and functions */
 size_t V3D_MMU_PAGE_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct v3d_dev* to_v3d_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ v3d_mmu_flush_all (struct v3d_dev*) ; 

void v3d_mmu_remove_ptes(struct v3d_bo *bo)
{
	struct v3d_dev *v3d = to_v3d_dev(bo->base.base.dev);
	u32 npages = bo->base.base.size >> V3D_MMU_PAGE_SHIFT;
	u32 page;

	for (page = bo->node.start; page < bo->node.start + npages; page++)
		v3d->pt[page] = 0;

	if (v3d_mmu_flush_all(v3d))
		dev_err(v3d->dev, "MMU flush timeout\n");
}