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
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  void* u32 ;
struct drm_gem_vram_object {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_crtc {TYPE_1__* dev; } ;
struct ast_private {int next_cursor; struct drm_gem_object* cursor_cache; } ;
struct ast_crtc {void* offset_y; void* offset_x; } ;
typedef  scalar_t__ s64 ;
struct TYPE_2__ {struct ast_private* dev_private; } ;

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
 int /*<<< orphan*/  DRM_ERROR (char*,void*) ; 
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ast_hide_cursor (struct drm_crtc*) ; 
 int /*<<< orphan*/  ast_set_index_reg (struct ast_private*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ast_show_cursor (struct drm_crtc*) ; 
 void* copy_cursor_image (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void*) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,void*) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/ * drm_gem_vram_kmap (struct drm_gem_vram_object*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_vram_kunmap (struct drm_gem_vram_object*) ; 
 struct drm_gem_vram_object* drm_gem_vram_of_gem (struct drm_gem_object*) ; 
 scalar_t__ drm_gem_vram_offset (struct drm_gem_vram_object*) ; 
 int drm_gem_vram_pin (struct drm_gem_vram_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_vram_unpin (struct drm_gem_vram_object*) ; 
 struct ast_crtc* to_ast_crtc (struct drm_crtc*) ; 
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
	struct drm_gem_vram_object *gbo;
	s64 dst_gpu;
	u64 gpu_addr;
	u32 csum;
	int ret;
	u8 *src, *dst;

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
	gbo = drm_gem_vram_of_gem(obj);

	ret = drm_gem_vram_pin(gbo, 0);
	if (ret)
		goto err_drm_gem_object_put_unlocked;
	src = drm_gem_vram_kmap(gbo, true, NULL);
	if (IS_ERR(src)) {
		ret = PTR_ERR(src);
		goto err_drm_gem_vram_unpin;
	}

	dst = drm_gem_vram_kmap(drm_gem_vram_of_gem(ast->cursor_cache),
				false, NULL);
	if (IS_ERR(dst)) {
		ret = PTR_ERR(dst);
		goto err_drm_gem_vram_kunmap;
	}
	dst_gpu = drm_gem_vram_offset(drm_gem_vram_of_gem(ast->cursor_cache));
	if (dst_gpu < 0) {
		ret = (int)dst_gpu;
		goto err_drm_gem_vram_kunmap;
	}

	dst += (AST_HWC_SIZE + AST_HWC_SIGNATURE_SIZE)*ast->next_cursor;

	/* do data transfer to cursor cache */
	csum = copy_cursor_image(src, dst, width, height);

	/* write checksum + signature */
	{
		struct drm_gem_vram_object *dst_gbo =
			drm_gem_vram_of_gem(ast->cursor_cache);
		u8 *dst = drm_gem_vram_kmap(dst_gbo, false, NULL);
		dst += (AST_HWC_SIZE + AST_HWC_SIGNATURE_SIZE)*ast->next_cursor + AST_HWC_SIZE;
		writel(csum, dst);
		writel(width, dst + AST_HWC_SIGNATURE_SizeX);
		writel(height, dst + AST_HWC_SIGNATURE_SizeY);
		writel(0, dst + AST_HWC_SIGNATURE_HOTSPOTX);
		writel(0, dst + AST_HWC_SIGNATURE_HOTSPOTY);

		/* set pattern offset */
		gpu_addr = (u64)dst_gpu;
		gpu_addr += (AST_HWC_SIZE + AST_HWC_SIGNATURE_SIZE)*ast->next_cursor;
		gpu_addr >>= 3;
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc8, gpu_addr & 0xff);
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc9, (gpu_addr >> 8) & 0xff);
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xca, (gpu_addr >> 16) & 0xff);
	}
	ast_crtc->offset_x = AST_MAX_HWC_WIDTH - width;
	ast_crtc->offset_y = AST_MAX_HWC_WIDTH - height;

	ast->next_cursor = (ast->next_cursor + 1) % AST_DEFAULT_HWC_NUM;

	ast_show_cursor(crtc);

	drm_gem_vram_kunmap(gbo);
	drm_gem_vram_unpin(gbo);
	drm_gem_object_put_unlocked(obj);

	return 0;

err_drm_gem_vram_kunmap:
	drm_gem_vram_kunmap(gbo);
err_drm_gem_vram_unpin:
	drm_gem_vram_unpin(gbo);
err_drm_gem_object_put_unlocked:
	drm_gem_object_put_unlocked(obj);
	return ret;
}