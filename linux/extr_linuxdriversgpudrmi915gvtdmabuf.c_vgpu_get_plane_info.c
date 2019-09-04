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
struct intel_vgpu_primary_plane_format {int base; int width; int height; int stride; int tiled; int bpp; int /*<<< orphan*/  drm_format; int /*<<< orphan*/  base_gpa; } ;
struct intel_vgpu_fb_info {int start; int width; int height; int stride; int size; void* y_hot; void* x_hot; int /*<<< orphan*/  y_pos; int /*<<< orphan*/  x_pos; scalar_t__ drm_format_mod; int /*<<< orphan*/  drm_format; int /*<<< orphan*/  start_gpa; } ;
struct intel_vgpu_cursor_plane_format {int base; int width; int height; int bpp; void* y_hot; void* x_hot; int /*<<< orphan*/  y_pos; int /*<<< orphan*/  x_pos; int /*<<< orphan*/  drm_format; int /*<<< orphan*/  base_gpa; } ;
struct intel_vgpu {int dummy; } ;
struct drm_i915_private {int /*<<< orphan*/  ggtt; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DRM_FORMAT_MOD_LINEAR ; 
 int DRM_PLANE_TYPE_CURSOR ; 
 int DRM_PLANE_TYPE_PRIMARY ; 
 int EFAULT ; 
 int EINVAL ; 
 scalar_t__ I915_FORMAT_MOD_X_TILED ; 
 scalar_t__ I915_FORMAT_MOD_Y_TILED ; 
 scalar_t__ I915_FORMAT_MOD_Yf_TILED ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
#define  PLANE_CTL_TILED_LINEAR 131 
#define  PLANE_CTL_TILED_X 130 
#define  PLANE_CTL_TILED_Y 129 
#define  PLANE_CTL_TILED_YF 128 
 void* UINT_MAX ; 
 int ggtt_total_entries (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*,...) ; 
 int /*<<< orphan*/  intel_gvt_ggtt_validate_range (struct intel_vgpu*,int,int) ; 
 int intel_vgpu_decode_cursor_plane (struct intel_vgpu*,struct intel_vgpu_cursor_plane_format*) ; 
 int intel_vgpu_decode_primary_plane (struct intel_vgpu*,struct intel_vgpu_primary_plane_format*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 scalar_t__ validate_hotspot (struct intel_vgpu_cursor_plane_format*) ; 

__attribute__((used)) static int vgpu_get_plane_info(struct drm_device *dev,
		struct intel_vgpu *vgpu,
		struct intel_vgpu_fb_info *info,
		int plane_id)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_vgpu_primary_plane_format p;
	struct intel_vgpu_cursor_plane_format c;
	int ret;

	if (plane_id == DRM_PLANE_TYPE_PRIMARY) {
		ret = intel_vgpu_decode_primary_plane(vgpu, &p);
		if (ret)
			return ret;
		info->start = p.base;
		info->start_gpa = p.base_gpa;
		info->width = p.width;
		info->height = p.height;
		info->stride = p.stride;
		info->drm_format = p.drm_format;

		switch (p.tiled) {
		case PLANE_CTL_TILED_LINEAR:
			info->drm_format_mod = DRM_FORMAT_MOD_LINEAR;
			break;
		case PLANE_CTL_TILED_X:
			info->drm_format_mod = I915_FORMAT_MOD_X_TILED;
			break;
		case PLANE_CTL_TILED_Y:
			info->drm_format_mod = I915_FORMAT_MOD_Y_TILED;
			break;
		case PLANE_CTL_TILED_YF:
			info->drm_format_mod = I915_FORMAT_MOD_Yf_TILED;
			break;
		default:
			gvt_vgpu_err("invalid tiling mode: %x\n", p.tiled);
		}

		info->size = (((p.stride * p.height * p.bpp) / 8) +
			      (PAGE_SIZE - 1)) >> PAGE_SHIFT;
	} else if (plane_id == DRM_PLANE_TYPE_CURSOR) {
		ret = intel_vgpu_decode_cursor_plane(vgpu, &c);
		if (ret)
			return ret;
		info->start = c.base;
		info->start_gpa = c.base_gpa;
		info->width = c.width;
		info->height = c.height;
		info->stride = c.width * (c.bpp / 8);
		info->drm_format = c.drm_format;
		info->drm_format_mod = 0;
		info->x_pos = c.x_pos;
		info->y_pos = c.y_pos;

		if (validate_hotspot(&c)) {
			info->x_hot = c.x_hot;
			info->y_hot = c.y_hot;
		} else {
			info->x_hot = UINT_MAX;
			info->y_hot = UINT_MAX;
		}

		info->size = (((info->stride * c.height * c.bpp) / 8)
				+ (PAGE_SIZE - 1)) >> PAGE_SHIFT;
	} else {
		gvt_vgpu_err("invalid plane id:%d\n", plane_id);
		return -EINVAL;
	}

	if (info->size == 0) {
		gvt_vgpu_err("fb size is zero\n");
		return -EINVAL;
	}

	if (info->start & (PAGE_SIZE - 1)) {
		gvt_vgpu_err("Not aligned fb address:0x%llx\n", info->start);
		return -EFAULT;
	}
	if (((info->start >> PAGE_SHIFT) + info->size) >
		ggtt_total_entries(&dev_priv->ggtt)) {
		gvt_vgpu_err("Invalid GTT offset or size\n");
		return -EFAULT;
	}

	if (!intel_gvt_ggtt_validate_range(vgpu, info->start, info->size)) {
		gvt_vgpu_err("invalid gma addr\n");
		return -EFAULT;
	}

	return 0;
}