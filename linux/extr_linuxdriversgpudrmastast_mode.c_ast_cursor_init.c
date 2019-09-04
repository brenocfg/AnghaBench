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
typedef  int /*<<< orphan*/  uint64_t ;
struct drm_gem_object {int dummy; } ;
struct drm_device {struct ast_private* dev_private; } ;
struct ast_private {int /*<<< orphan*/  cursor_cache_gpu_addr; struct drm_gem_object* cursor_cache; int /*<<< orphan*/  cache_kmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_pages; } ;
struct ast_bo {TYPE_1__ bo; } ;

/* Variables and functions */
 int AST_DEFAULT_HWC_NUM ; 
 int AST_HWC_SIGNATURE_SIZE ; 
 int AST_HWC_SIZE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTM_PL_FLAG_VRAM ; 
 int ast_bo_pin (struct ast_bo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ast_bo_reserve (struct ast_bo*,int) ; 
 int /*<<< orphan*/  ast_bo_unreserve (struct ast_bo*) ; 
 int ast_gem_create (struct drm_device*,int,int,struct drm_gem_object**) ; 
 struct ast_bo* gem_to_ast_bo (struct drm_gem_object*) ; 
 int ttm_bo_kmap (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ast_cursor_init(struct drm_device *dev)
{
	struct ast_private *ast = dev->dev_private;
	int size;
	int ret;
	struct drm_gem_object *obj;
	struct ast_bo *bo;
	uint64_t gpu_addr;

	size = (AST_HWC_SIZE + AST_HWC_SIGNATURE_SIZE) * AST_DEFAULT_HWC_NUM;

	ret = ast_gem_create(dev, size, true, &obj);
	if (ret)
		return ret;
	bo = gem_to_ast_bo(obj);
	ret = ast_bo_reserve(bo, false);
	if (unlikely(ret != 0))
		goto fail;

	ret = ast_bo_pin(bo, TTM_PL_FLAG_VRAM, &gpu_addr);
	ast_bo_unreserve(bo);
	if (ret)
		goto fail;

	/* kmap the object */
	ret = ttm_bo_kmap(&bo->bo, 0, bo->bo.num_pages, &ast->cache_kmap);
	if (ret)
		goto fail;

	ast->cursor_cache = obj;
	ast->cursor_cache_gpu_addr = gpu_addr;
	DRM_DEBUG_KMS("pinned cursor cache at %llx\n", ast->cursor_cache_gpu_addr);
	return 0;
fail:
	return ret;
}