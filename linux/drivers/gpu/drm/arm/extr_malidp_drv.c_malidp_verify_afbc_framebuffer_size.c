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
typedef  int u32 ;
struct drm_mode_fb_cmd2 {int* modifier; int width; int height; int* pitches; int /*<<< orphan*/ * handles; } ;
struct drm_gem_object {int size; } ;
struct drm_format_info {int /*<<< orphan*/  format; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int AFBC_HEADER_SIZE ; 
#define  AFBC_SIZE_16X16 128 
 int AFBC_SIZE_MASK ; 
 int /*<<< orphan*/  AFBC_SUPERBLK_ALIGNMENT ; 
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int BITS_PER_BYTE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct drm_format_info* drm_get_format_info (struct drm_device*,struct drm_mode_fb_cmd2 const*) ; 
 int malidp_format_get_bpp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
malidp_verify_afbc_framebuffer_size(struct drm_device *dev,
				    struct drm_file *file,
				    const struct drm_mode_fb_cmd2 *mode_cmd)
{
	int n_superblocks = 0;
	const struct drm_format_info *info;
	struct drm_gem_object *objs = NULL;
	u32 afbc_superblock_size = 0, afbc_superblock_height = 0;
	u32 afbc_superblock_width = 0, afbc_size = 0;
	int bpp = 0;

	switch (mode_cmd->modifier[0] & AFBC_SIZE_MASK) {
	case AFBC_SIZE_16X16:
		afbc_superblock_height = 16;
		afbc_superblock_width = 16;
		break;
	default:
		DRM_DEBUG_KMS("AFBC superblock size is not supported\n");
		return false;
	}

	info = drm_get_format_info(dev, mode_cmd);

	n_superblocks = (mode_cmd->width / afbc_superblock_width) *
		(mode_cmd->height / afbc_superblock_height);

	bpp = malidp_format_get_bpp(info->format);

	afbc_superblock_size = (bpp * afbc_superblock_width * afbc_superblock_height)
				/ BITS_PER_BYTE;

	afbc_size = ALIGN(n_superblocks * AFBC_HEADER_SIZE, AFBC_SUPERBLK_ALIGNMENT);
	afbc_size += n_superblocks * ALIGN(afbc_superblock_size, AFBC_SUPERBLK_ALIGNMENT);

	if ((mode_cmd->width * bpp) != (mode_cmd->pitches[0] * BITS_PER_BYTE)) {
		DRM_DEBUG_KMS("Invalid value of (pitch * BITS_PER_BYTE) (=%u) "
			      "should be same as width (=%u) * bpp (=%u)\n",
			      (mode_cmd->pitches[0] * BITS_PER_BYTE),
			      mode_cmd->width, bpp);
		return false;
	}

	objs = drm_gem_object_lookup(file, mode_cmd->handles[0]);
	if (!objs) {
		DRM_DEBUG_KMS("Failed to lookup GEM object\n");
		return false;
	}

	if (objs->size < afbc_size) {
		DRM_DEBUG_KMS("buffer size (%zu) too small for AFBC buffer size = %u\n",
			      objs->size, afbc_size);
		drm_gem_object_put_unlocked(objs);
		return false;
	}

	drm_gem_object_put_unlocked(objs);

	return true;
}