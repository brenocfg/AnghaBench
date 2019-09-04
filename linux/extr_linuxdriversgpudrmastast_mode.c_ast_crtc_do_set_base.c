#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct drm_gem_object {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_crtc {TYPE_2__* primary; TYPE_1__* dev; } ;
struct ast_private {TYPE_3__* fbdev; } ;
struct ast_framebuffer {struct drm_gem_object* obj; } ;
struct TYPE_8__ {int /*<<< orphan*/  num_pages; } ;
struct ast_bo {int /*<<< orphan*/  kmap; TYPE_4__ bo; } ;
struct TYPE_7__ {struct ast_framebuffer afb; } ;
struct TYPE_6__ {struct drm_framebuffer* fb; } ;
struct TYPE_5__ {struct ast_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  TTM_PL_FLAG_VRAM ; 
 int ast_bo_pin (struct ast_bo*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ast_bo_push_sysram (struct ast_bo*) ; 
 int ast_bo_reserve (struct ast_bo*,int) ; 
 int /*<<< orphan*/  ast_bo_unreserve (struct ast_bo*) ; 
 int /*<<< orphan*/  ast_fbdev_set_base (struct ast_private*,scalar_t__) ; 
 int /*<<< orphan*/  ast_set_offset_reg (struct drm_crtc*) ; 
 int /*<<< orphan*/  ast_set_start_address_crt1 (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 struct ast_bo* gem_to_ast_bo (struct drm_gem_object*) ; 
 struct ast_framebuffer* to_ast_framebuffer (struct drm_framebuffer*) ; 
 int ttm_bo_kmap (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ast_crtc_do_set_base(struct drm_crtc *crtc,
				struct drm_framebuffer *fb,
				int x, int y, int atomic)
{
	struct ast_private *ast = crtc->dev->dev_private;
	struct drm_gem_object *obj;
	struct ast_framebuffer *ast_fb;
	struct ast_bo *bo;
	int ret;
	u64 gpu_addr;

	/* push the previous fb to system ram */
	if (!atomic && fb) {
		ast_fb = to_ast_framebuffer(fb);
		obj = ast_fb->obj;
		bo = gem_to_ast_bo(obj);
		ret = ast_bo_reserve(bo, false);
		if (ret)
			return ret;
		ast_bo_push_sysram(bo);
		ast_bo_unreserve(bo);
	}

	ast_fb = to_ast_framebuffer(crtc->primary->fb);
	obj = ast_fb->obj;
	bo = gem_to_ast_bo(obj);

	ret = ast_bo_reserve(bo, false);
	if (ret)
		return ret;

	ret = ast_bo_pin(bo, TTM_PL_FLAG_VRAM, &gpu_addr);
	if (ret) {
		ast_bo_unreserve(bo);
		return ret;
	}

	if (&ast->fbdev->afb == ast_fb) {
		/* if pushing console in kmap it */
		ret = ttm_bo_kmap(&bo->bo, 0, bo->bo.num_pages, &bo->kmap);
		if (ret)
			DRM_ERROR("failed to kmap fbcon\n");
		else
			ast_fbdev_set_base(ast, gpu_addr);
	}
	ast_bo_unreserve(bo);

	ast_set_offset_reg(crtc);
	ast_set_start_address_crt1(crtc, (u32)gpu_addr);

	return 0;
}