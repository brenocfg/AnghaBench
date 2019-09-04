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
struct TYPE_6__ {int /*<<< orphan*/ * release; } ;
struct TYPE_4__ {TYPE_3__ ref; } ;
struct TYPE_5__ {TYPE_3__ mem_global_ref; TYPE_1__ bo_global_ref; } ;
struct nouveau_drm {TYPE_2__ ttm; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_global_item_unref (TYPE_3__*) ; 

void
nouveau_ttm_global_release(struct nouveau_drm *drm)
{
	if (drm->ttm.mem_global_ref.release == NULL)
		return;

	drm_global_item_unref(&drm->ttm.bo_global_ref.ref);
	drm_global_item_unref(&drm->ttm.mem_global_ref);
	drm->ttm.mem_global_ref.release = NULL;
}