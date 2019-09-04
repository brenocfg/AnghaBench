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
struct vfio_device_gfx_plane_info {int /*<<< orphan*/  y_hot; int /*<<< orphan*/  x_hot; int /*<<< orphan*/  y_pos; int /*<<< orphan*/  x_pos; int /*<<< orphan*/  size; int /*<<< orphan*/  stride; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  drm_format_mod; int /*<<< orphan*/  drm_format; } ;
struct intel_vgpu_fb_info {int /*<<< orphan*/  y_hot; int /*<<< orphan*/  x_hot; int /*<<< orphan*/  y_pos; int /*<<< orphan*/  x_pos; int /*<<< orphan*/  size; int /*<<< orphan*/  stride; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  drm_format_mod; int /*<<< orphan*/  drm_format; } ;

/* Variables and functions */

__attribute__((used)) static void update_fb_info(struct vfio_device_gfx_plane_info *gvt_dmabuf,
		      struct intel_vgpu_fb_info *fb_info)
{
	gvt_dmabuf->drm_format = fb_info->drm_format;
	gvt_dmabuf->drm_format_mod = fb_info->drm_format_mod;
	gvt_dmabuf->width = fb_info->width;
	gvt_dmabuf->height = fb_info->height;
	gvt_dmabuf->stride = fb_info->stride;
	gvt_dmabuf->size = fb_info->size;
	gvt_dmabuf->x_pos = fb_info->x_pos;
	gvt_dmabuf->y_pos = fb_info->y_pos;
	gvt_dmabuf->x_hot = fb_info->x_hot;
	gvt_dmabuf->y_hot = fb_info->y_hot;
}