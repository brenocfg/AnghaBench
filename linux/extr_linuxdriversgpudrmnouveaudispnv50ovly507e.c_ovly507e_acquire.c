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
struct TYPE_6__ {struct drm_framebuffer* fb; } ;
struct nv50_wndw_atom {TYPE_3__ state; } ;
struct nv50_wndw {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  cpp; } ;
struct nv50_head_atom {TYPE_2__ ovly; int /*<<< orphan*/  state; } ;
struct drm_framebuffer {TYPE_1__* format; } ;
struct TYPE_4__ {int /*<<< orphan*/ * cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_PLANE_HELPER_NO_SCALING ; 
 int drm_atomic_helper_check_plane_state (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int
ovly507e_acquire(struct nv50_wndw *wndw, struct nv50_wndw_atom *asyw,
		 struct nv50_head_atom *asyh)
{
	const struct drm_framebuffer *fb = asyw->state.fb;
	int ret;

	ret = drm_atomic_helper_check_plane_state(&asyw->state, &asyh->state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  true, true);
	if (ret)
		return ret;

	asyh->ovly.cpp = fb->format->cpp[0];
	return 0;
}