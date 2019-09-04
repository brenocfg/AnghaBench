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
struct qxl_rect {int /*<<< orphan*/  bottom; scalar_t__ top; int /*<<< orphan*/  right; scalar_t__ left; } ;
struct qxl_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct qxl_bo {TYPE_1__ surf; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int qxl_io_update_area (struct qxl_device*,struct qxl_bo*,struct qxl_rect*) ; 

__attribute__((used)) static int qxl_update_surface(struct qxl_device *qdev, struct qxl_bo *surf)
{
	struct qxl_rect rect;
	int ret;

	/* if we are evicting, we need to make sure the surface is up
	   to date */
	rect.left = 0;
	rect.right = surf->surf.width;
	rect.top = 0;
	rect.bottom = surf->surf.height;
retry:
	ret = qxl_io_update_area(qdev, surf, &rect);
	if (ret == -ERESTARTSYS)
		goto retry;
	return ret;
}