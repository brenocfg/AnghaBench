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
struct qxl_surface {int width; scalar_t__ height; int stride; int /*<<< orphan*/  format; } ;
struct qxl_head {int x; scalar_t__ height; scalar_t__ width; } ;
struct qxl_device {TYPE_3__* dumb_shadow_bo; struct qxl_head* dumb_heads; TYPE_1__* monitors_config; } ;
struct TYPE_5__ {int width; int height; } ;
struct TYPE_6__ {TYPE_2__ surf; } ;
struct TYPE_4__ {int max_allowed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int,int) ; 
 int /*<<< orphan*/  SPICE_SURFACE_FMT_32_xRGB ; 
 int /*<<< orphan*/  memset (struct qxl_surface*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qxl_calc_dumb_shadow(struct qxl_device *qdev,
				 struct qxl_surface *surf)
{
	struct qxl_head *head;
	int i;

	memset(surf, 0, sizeof(*surf));
	for (i = 0; i < qdev->monitors_config->max_allowed; i++) {
		head = qdev->dumb_heads + i;
		head->x = surf->width;
		surf->width += head->width;
		if (surf->height < head->height)
			surf->height = head->height;
	}
	if (surf->width < 64)
		surf->width = 64;
	if (surf->height < 64)
		surf->height = 64;
	surf->format = SPICE_SURFACE_FMT_32_xRGB;
	surf->stride = surf->width * 4;

	if (!qdev->dumb_shadow_bo ||
	    qdev->dumb_shadow_bo->surf.width != surf->width ||
	    qdev->dumb_shadow_bo->surf.height != surf->height)
		DRM_DEBUG("%dx%d\n", surf->width, surf->height);
}