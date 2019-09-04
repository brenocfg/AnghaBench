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
struct qxl_framebuffer {int /*<<< orphan*/  obj; } ;
struct qxl_device {int vram_size; } ;
struct TYPE_3__ {int stride; int height; } ;
struct qxl_bo {TYPE_1__ surf; } ;
struct drm_plane_state {int /*<<< orphan*/  fb; int /*<<< orphan*/  crtc; } ;
struct drm_plane {TYPE_2__* dev; } ;
struct TYPE_4__ {struct qxl_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 struct qxl_bo* gem_to_qxl_bo (int /*<<< orphan*/ ) ; 
 struct qxl_framebuffer* to_qxl_framebuffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qxl_primary_atomic_check(struct drm_plane *plane,
				    struct drm_plane_state *state)
{
	struct qxl_device *qdev = plane->dev->dev_private;
	struct qxl_framebuffer *qfb;
	struct qxl_bo *bo;

	if (!state->crtc || !state->fb)
		return 0;

	qfb = to_qxl_framebuffer(state->fb);
	bo = gem_to_qxl_bo(qfb->obj);

	if (bo->surf.stride * bo->surf.height > qdev->vram_size) {
		DRM_ERROR("Mode doesn't fit in vram size (vgamem)");
		return -EINVAL;
	}

	return 0;
}