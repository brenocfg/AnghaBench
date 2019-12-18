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
struct qxl_device {int dummy; } ;
struct qxl_bo {int is_primary; } ;
struct drm_plane_state {TYPE_2__* fb; } ;
struct drm_plane {TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * obj; } ;
struct TYPE_3__ {struct qxl_device* dev_private; } ;

/* Variables and functions */
 struct qxl_bo* gem_to_qxl_bo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qxl_io_destroy_primary (struct qxl_device*) ; 

__attribute__((used)) static void qxl_primary_atomic_disable(struct drm_plane *plane,
				       struct drm_plane_state *old_state)
{
	struct qxl_device *qdev = plane->dev->dev_private;

	if (old_state->fb) {
		struct qxl_bo *bo = gem_to_qxl_bo(old_state->fb->obj[0]);

		if (bo->is_primary) {
			qxl_io_destroy_primary(qdev);
			bo->is_primary = false;
		}
	}
}