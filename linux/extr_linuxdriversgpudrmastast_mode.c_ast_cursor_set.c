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
typedef  int uint64_t ;
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
struct ttm_bo_kmap_obj {scalar_t__ virtual; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_crtc {TYPE_1__* dev; } ;
struct ast_private {int next_cursor; int cursor_cache_gpu_addr; struct ttm_bo_kmap_obj cache_kmap; } ;
struct ast_crtc {void* offset_y; void* offset_x; void* cursor_height; void* cursor_width; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_pages; } ;
struct ast_bo {TYPE_2__ bo; } ;
struct TYPE_3__ {struct ast_private* dev_private; } ;

/* Variables and functions */
 int AST_DEFAULT_HWC_NUM ; 
 int AST_HWC_SIGNATURE_HOTSPOTX ; 
 int AST_HWC_SIGNATURE_HOTSPOTY ; 
 int AST_HWC_SIGNATURE_SIZE ; 
 int AST_HWC_SIGNATURE_SizeX ; 
 int AST_HWC_SIGNATURE_SizeY ; 
 int AST_HWC_SIZE ; 
 int /*<<< orphan*/  AST_IO_CRTC_PORT ; 
 void* AST_MAX_HWC_HEIGHT ; 
 void* AST_MAX_HWC_WIDTH ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int ENOENT ; 
 int ast_bo_reserve (struct ast_bo*,int) ; 
 int /*<<< orphan*/  ast_bo_unreserve (struct ast_bo*) ; 
 int /*<<< orphan*/  ast_hide_cursor (struct drm_crtc*) ; 
 int /*<<< orphan*/  ast_set_index_reg (struct ast_private*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ast_show_cursor (struct drm_crtc*) ; 
 void* copy_cursor_image (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void*) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,void*) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct ast_bo* gem_to_ast_bo (struct drm_gem_object*) ; 
 struct ast_crtc* to_ast_crtc (struct drm_crtc*) ; 
 int ttm_bo_kmap (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ttm_bo_kmap_obj*) ; 
 int /*<<< orphan*/  ttm_bo_kunmap (struct ttm_bo_kmap_obj*) ; 
 int /*<<< orphan*/ * ttm_kmap_obj_virtual (struct ttm_bo_kmap_obj*,int*) ; 
 int /*<<< orphan*/  writel (void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ast_cursor_set(struct drm_crtc *crtc,
			  struct drm_file *file_priv,
			  uint32_t handle,
			  uint32_t width,
			  uint32_t height)
{
	struct ast_private *ast = crtc->dev->dev_private;
	struct ast_crtc *ast_crtc = to_ast_crtc(crtc);
	struct drm_gem_object *obj;
	struct ast_bo *bo;
	uint64_t gpu_addr;
	u32 csum;
	int ret;
	struct ttm_bo_kmap_obj uobj_map;
	u8 *src, *dst;
	bool src_isiomem, dst_isiomem;
	if (!handle) {
		ast_hide_cursor(crtc);
		return 0;
	}

	if (width > AST_MAX_HWC_WIDTH || height > AST_MAX_HWC_HEIGHT)
		return -EINVAL;

	obj = drm_gem_object_lookup(file_priv, handle);
	if (!obj) {
		DRM_ERROR("Cannot find cursor object %x for crtc\n", handle);
		return -ENOENT;
	}
	bo = gem_to_ast_bo(obj);

	ret = ast_bo_reserve(bo, false);
	if (ret)
		goto fail;

	ret = ttm_bo_kmap(&bo->bo, 0, bo->bo.num_pages, &uobj_map);

	src = ttm_kmap_obj_virtual(&uobj_map, &src_isiomem);
	dst = ttm_kmap_obj_virtual(&ast->cache_kmap, &dst_isiomem);

	if (src_isiomem == true)
		DRM_ERROR("src cursor bo should be in main memory\n");
	if (dst_isiomem == false)
		DRM_ERROR("dst bo should be in VRAM\n");

	dst += (AST_HWC_SIZE + AST_HWC_SIGNATURE_SIZE)*ast->next_cursor;

	/* do data transfer to cursor cache */
	csum = copy_cursor_image(src, dst, width, height);

	/* write checksum + signature */
	ttm_bo_kunmap(&uobj_map);
	ast_bo_unreserve(bo);
	{
		u8 *dst = (u8 *)ast->cache_kmap.virtual + (AST_HWC_SIZE + AST_HWC_SIGNATURE_SIZE)*ast->next_cursor + AST_HWC_SIZE;
		writel(csum, dst);
		writel(width, dst + AST_HWC_SIGNATURE_SizeX);
		writel(height, dst + AST_HWC_SIGNATURE_SizeY);
		writel(0, dst + AST_HWC_SIGNATURE_HOTSPOTX);
		writel(0, dst + AST_HWC_SIGNATURE_HOTSPOTY);

		/* set pattern offset */
		gpu_addr = ast->cursor_cache_gpu_addr;
		gpu_addr += (AST_HWC_SIZE + AST_HWC_SIGNATURE_SIZE)*ast->next_cursor;
		gpu_addr >>= 3;
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc8, gpu_addr & 0xff);
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc9, (gpu_addr >> 8) & 0xff);
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xca, (gpu_addr >> 16) & 0xff);
	}
	ast_crtc->cursor_width = width;
	ast_crtc->cursor_height = height;
	ast_crtc->offset_x = AST_MAX_HWC_WIDTH - width;
	ast_crtc->offset_y = AST_MAX_HWC_WIDTH - height;

	ast->next_cursor = (ast->next_cursor + 1) % AST_DEFAULT_HWC_NUM;

	ast_show_cursor(crtc);

	drm_gem_object_put_unlocked(obj);
	return 0;
fail:
	drm_gem_object_put_unlocked(obj);
	return ret;
}