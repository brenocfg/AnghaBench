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
struct nv04_display {scalar_t__* image; } ;
struct nouveau_framebuffer {int /*<<< orphan*/  nvbo; } ;
struct nouveau_crtc {size_t index; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_crtc {TYPE_1__* primary; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_PL_FLAG_VRAM ; 
 int nouveau_bo_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nouveau_bo_ref (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  nouveau_bo_unpin (scalar_t__) ; 
 struct nouveau_crtc* nouveau_crtc (struct drm_crtc*) ; 
 struct nouveau_framebuffer* nouveau_framebuffer (int /*<<< orphan*/ ) ; 
 struct nv04_display* nv04_display (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv_crtc_swap_fbs(struct drm_crtc *crtc, struct drm_framebuffer *old_fb)
{
	struct nv04_display *disp = nv04_display(crtc->dev);
	struct nouveau_framebuffer *nvfb = nouveau_framebuffer(crtc->primary->fb);
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	int ret;

	ret = nouveau_bo_pin(nvfb->nvbo, TTM_PL_FLAG_VRAM, false);
	if (ret == 0) {
		if (disp->image[nv_crtc->index])
			nouveau_bo_unpin(disp->image[nv_crtc->index]);
		nouveau_bo_ref(nvfb->nvbo, &disp->image[nv_crtc->index]);
	}

	return ret;
}