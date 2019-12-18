#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drm_gem_vram_object {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_device {struct ast_private* dev_private; } ;
struct ast_private {struct drm_gem_object* cursor_cache; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int AST_DEFAULT_HWC_NUM ; 
 int AST_HWC_SIGNATURE_SIZE ; 
 int AST_HWC_SIZE ; 
 int /*<<< orphan*/  DRM_GEM_VRAM_PL_FLAG_VRAM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int ast_gem_create (struct drm_device*,int,int,struct drm_gem_object**) ; 
 void* drm_gem_vram_kmap (struct drm_gem_vram_object*,int,int /*<<< orphan*/ *) ; 
 struct drm_gem_vram_object* drm_gem_vram_of_gem (struct drm_gem_object*) ; 
 scalar_t__ drm_gem_vram_offset (struct drm_gem_vram_object*) ; 
 int drm_gem_vram_pin (struct drm_gem_vram_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_vram_unpin (struct drm_gem_vram_object*) ; 

__attribute__((used)) static int ast_cursor_init(struct drm_device *dev)
{
	struct ast_private *ast = dev->dev_private;
	int size;
	int ret;
	struct drm_gem_object *obj;
	struct drm_gem_vram_object *gbo;
	s64 gpu_addr;
	void *base;

	size = (AST_HWC_SIZE + AST_HWC_SIGNATURE_SIZE) * AST_DEFAULT_HWC_NUM;

	ret = ast_gem_create(dev, size, true, &obj);
	if (ret)
		return ret;
	gbo = drm_gem_vram_of_gem(obj);
	ret = drm_gem_vram_pin(gbo, DRM_GEM_VRAM_PL_FLAG_VRAM);
	if (ret)
		goto fail;
	gpu_addr = drm_gem_vram_offset(gbo);
	if (gpu_addr < 0) {
		drm_gem_vram_unpin(gbo);
		ret = (int)gpu_addr;
		goto fail;
	}

	/* kmap the object */
	base = drm_gem_vram_kmap(gbo, true, NULL);
	if (IS_ERR(base)) {
		ret = PTR_ERR(base);
		goto fail;
	}

	ast->cursor_cache = obj;
	return 0;
fail:
	return ret;
}