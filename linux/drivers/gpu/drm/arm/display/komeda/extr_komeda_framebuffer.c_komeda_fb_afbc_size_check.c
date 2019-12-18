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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct drm_framebuffer {int modifier; int width; int height; int* offsets; struct drm_gem_object** obj; struct drm_format_info* format; } ;
struct komeda_fb {int aligned_w; int aligned_h; int offset_payload; scalar_t__ afbc_size; struct drm_framebuffer base; } ;
struct drm_mode_fb_cmd2 {int /*<<< orphan*/ * handles; } ;
struct drm_gem_object {scalar_t__ size; } ;
struct drm_format_info {int dummy; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 int AFBC_BODY_START_ALIGNMENT ; 
#define  AFBC_FORMAT_MOD_BLOCK_SIZE_16x16 129 
#define  AFBC_FORMAT_MOD_BLOCK_SIZE_32x8 128 
 int AFBC_FORMAT_MOD_BLOCK_SIZE_MASK ; 
 int AFBC_FORMAT_MOD_TILED ; 
 int AFBC_HEADER_SIZE ; 
 int AFBC_SUPERBLK_ALIGNMENT ; 
 int AFBC_SUPERBLK_PIXELS ; 
 int AFBC_TH_BODY_START_ALIGNMENT ; 
 int AFBC_TH_LAYOUT_ALIGNMENT ; 
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int komeda_get_afbc_format_bpp (struct drm_format_info const*,int) ; 

__attribute__((used)) static int
komeda_fb_afbc_size_check(struct komeda_fb *kfb, struct drm_file *file,
			  const struct drm_mode_fb_cmd2 *mode_cmd)
{
	struct drm_framebuffer *fb = &kfb->base;
	const struct drm_format_info *info = fb->format;
	struct drm_gem_object *obj;
	u32 alignment_w = 0, alignment_h = 0, alignment_header, n_blocks, bpp;
	u64 min_size;

	obj = drm_gem_object_lookup(file, mode_cmd->handles[0]);
	if (!obj) {
		DRM_DEBUG_KMS("Failed to lookup GEM object\n");
		return -ENOENT;
	}

	switch (fb->modifier & AFBC_FORMAT_MOD_BLOCK_SIZE_MASK) {
	case AFBC_FORMAT_MOD_BLOCK_SIZE_32x8:
		alignment_w = 32;
		alignment_h = 8;
		break;
	case AFBC_FORMAT_MOD_BLOCK_SIZE_16x16:
		alignment_w = 16;
		alignment_h = 16;
		break;
	default:
		WARN(1, "Invalid AFBC_FORMAT_MOD_BLOCK_SIZE: %lld.\n",
		     fb->modifier & AFBC_FORMAT_MOD_BLOCK_SIZE_MASK);
		break;
	}

	/* tiled header afbc */
	if (fb->modifier & AFBC_FORMAT_MOD_TILED) {
		alignment_w *= AFBC_TH_LAYOUT_ALIGNMENT;
		alignment_h *= AFBC_TH_LAYOUT_ALIGNMENT;
		alignment_header = AFBC_TH_BODY_START_ALIGNMENT;
	} else {
		alignment_header = AFBC_BODY_START_ALIGNMENT;
	}

	kfb->aligned_w = ALIGN(fb->width, alignment_w);
	kfb->aligned_h = ALIGN(fb->height, alignment_h);

	if (fb->offsets[0] % alignment_header) {
		DRM_DEBUG_KMS("afbc offset alignment check failed.\n");
		goto check_failed;
	}

	n_blocks = (kfb->aligned_w * kfb->aligned_h) / AFBC_SUPERBLK_PIXELS;
	kfb->offset_payload = ALIGN(n_blocks * AFBC_HEADER_SIZE,
				    alignment_header);

	bpp = komeda_get_afbc_format_bpp(info, fb->modifier);
	kfb->afbc_size = kfb->offset_payload + n_blocks *
			 ALIGN(bpp * AFBC_SUPERBLK_PIXELS / 8,
			       AFBC_SUPERBLK_ALIGNMENT);
	min_size = kfb->afbc_size + fb->offsets[0];
	if (min_size > obj->size) {
		DRM_DEBUG_KMS("afbc size check failed, obj_size: 0x%zx. min_size 0x%llx.\n",
			      obj->size, min_size);
		goto check_failed;
	}

	fb->obj[0] = obj;
	return 0;

check_failed:
	drm_gem_object_put_unlocked(obj);
	return -EINVAL;
}