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
typedef  int /*<<< orphan*/  u32 ;
struct drm_gem_vram_object {int dummy; } ;
struct drm_framebuffer {int /*<<< orphan*/ * obj; } ;
struct drm_crtc {TYPE_2__* primary; } ;
typedef  scalar_t__ s64 ;
struct TYPE_4__ {TYPE_1__* fb; } ;
struct TYPE_3__ {int /*<<< orphan*/ * obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_GEM_VRAM_PL_FLAG_VRAM ; 
 int /*<<< orphan*/  ast_set_offset_reg (struct drm_crtc*) ; 
 int /*<<< orphan*/  ast_set_start_address_crt1 (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 struct drm_gem_vram_object* drm_gem_vram_of_gem (int /*<<< orphan*/ ) ; 
 scalar_t__ drm_gem_vram_offset (struct drm_gem_vram_object*) ; 
 int drm_gem_vram_pin (struct drm_gem_vram_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_vram_unpin (struct drm_gem_vram_object*) ; 

__attribute__((used)) static int ast_crtc_do_set_base(struct drm_crtc *crtc,
				struct drm_framebuffer *fb,
				int x, int y, int atomic)
{
	struct drm_gem_vram_object *gbo;
	int ret;
	s64 gpu_addr;

	if (!atomic && fb) {
		gbo = drm_gem_vram_of_gem(fb->obj[0]);
		drm_gem_vram_unpin(gbo);
	}

	gbo = drm_gem_vram_of_gem(crtc->primary->fb->obj[0]);

	ret = drm_gem_vram_pin(gbo, DRM_GEM_VRAM_PL_FLAG_VRAM);
	if (ret)
		return ret;
	gpu_addr = drm_gem_vram_offset(gbo);
	if (gpu_addr < 0) {
		ret = (int)gpu_addr;
		goto err_drm_gem_vram_unpin;
	}

	ast_set_offset_reg(crtc);
	ast_set_start_address_crt1(crtc, (u32)gpu_addr);

	return 0;

err_drm_gem_vram_unpin:
	drm_gem_vram_unpin(gbo);
	return ret;
}