#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int x1; int y1; } ;
struct TYPE_11__ {struct drm_framebuffer* fb; TYPE_3__ src; } ;
struct nv50_wndw_atom {TYPE_5__ state; } ;
struct nv50_wndw {TYPE_1__* func; } ;
struct TYPE_10__ {int cpp; int depth; int x; int y; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_12__ {int color_mgmt_changed; } ;
struct nv50_head_atom {TYPE_4__ base; TYPE_6__ state; } ;
struct drm_framebuffer {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_2__* format; } ;
struct TYPE_8__ {int* cpp; int depth; } ;
struct TYPE_7__ {int /*<<< orphan*/  ilut; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_PLANE_HELPER_NO_SCALING ; 
 int drm_atomic_helper_check_plane_state (TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int
base507c_acquire(struct nv50_wndw *wndw, struct nv50_wndw_atom *asyw,
		 struct nv50_head_atom *asyh)
{
	const struct drm_framebuffer *fb = asyw->state.fb;
	int ret;

	ret = drm_atomic_helper_check_plane_state(&asyw->state, &asyh->state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  false, true);
	if (ret)
		return ret;

	if (!wndw->func->ilut) {
		if ((asyh->base.cpp != 1) ^ (fb->format->cpp[0] != 1))
			asyh->state.color_mgmt_changed = true;
	}

	asyh->base.depth = fb->format->depth;
	asyh->base.cpp = fb->format->cpp[0];
	asyh->base.x = asyw->state.src.x1 >> 16;
	asyh->base.y = asyw->state.src.y1 >> 16;
	asyh->base.w = asyw->state.fb->width;
	asyh->base.h = asyw->state.fb->height;

	/* Some newer formats, esp FP16 ones, don't have a
	 * "depth". There's nothing that really makes sense there
	 * either, so just set it to the implicit bit count.
	 */
	if (!asyh->base.depth)
		asyh->base.depth = asyh->base.cpp * 8;

	return 0;
}