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
struct TYPE_3__ {int /*<<< orphan*/  ref; } ;
struct TYPE_4__ {int mem_global_referenced; int /*<<< orphan*/  mem_global_ref; TYPE_1__ bo_global_ref; } ;
struct qxl_device {TYPE_2__ mman; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_global_item_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qxl_ttm_global_fini(struct qxl_device *qdev)
{
	if (qdev->mman.mem_global_referenced) {
		drm_global_item_unref(&qdev->mman.bo_global_ref.ref);
		drm_global_item_unref(&qdev->mman.mem_global_ref);
		qdev->mman.mem_global_referenced = false;
	}
}