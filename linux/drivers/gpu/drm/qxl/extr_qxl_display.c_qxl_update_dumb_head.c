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
typedef  scalar_t__ uint32_t ;
struct qxl_device {TYPE_3__* dumb_heads; TYPE_1__* monitors_config; } ;
struct TYPE_5__ {scalar_t__ width; scalar_t__ height; } ;
struct qxl_bo {TYPE_2__ surf; scalar_t__ is_dumb; } ;
struct TYPE_6__ {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_4__ {int max_allowed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void qxl_update_dumb_head(struct qxl_device *qdev,
				 int index, struct qxl_bo *bo)
{
	uint32_t width, height;

	if (index >= qdev->monitors_config->max_allowed)
		return;

	if (bo && bo->is_dumb) {
		width = bo->surf.width;
		height = bo->surf.height;
	} else {
		width = 0;
		height = 0;
	}

	if (qdev->dumb_heads[index].width == width &&
	    qdev->dumb_heads[index].height == height)
		return;

	DRM_DEBUG("#%d: %dx%d -> %dx%d\n", index,
		  qdev->dumb_heads[index].width,
		  qdev->dumb_heads[index].height,
		  width, height);
	qdev->dumb_heads[index].width = width;
	qdev->dumb_heads[index].height = height;
}