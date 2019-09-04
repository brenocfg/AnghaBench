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
struct drm_vmw_gb_surface_create_rep {int dummy; } ;
union drm_vmw_gb_surface_create_arg {int /*<<< orphan*/  req; struct drm_vmw_gb_surface_create_rep rep; } ;
struct drm_vmw_gb_surface_create_ext_req {scalar_t__ must_be_zero; int /*<<< orphan*/  quality_level; int /*<<< orphan*/  multisample_pattern; scalar_t__ svga3d_flags_upper_32_bits; int /*<<< orphan*/  version; int /*<<< orphan*/  base; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVGA3D_MS_PATTERN_NONE ; 
 int /*<<< orphan*/  SVGA3D_MS_QUALITY_NONE ; 
 int /*<<< orphan*/  drm_vmw_gb_surface_v1 ; 
 int vmw_gb_surface_define_internal (struct drm_device*,struct drm_vmw_gb_surface_create_ext_req*,struct drm_vmw_gb_surface_create_rep*,struct drm_file*) ; 

int vmw_gb_surface_define_ioctl(struct drm_device *dev, void *data,
				struct drm_file *file_priv)
{
	union drm_vmw_gb_surface_create_arg *arg =
	    (union drm_vmw_gb_surface_create_arg *)data;
	struct drm_vmw_gb_surface_create_rep *rep = &arg->rep;
	struct drm_vmw_gb_surface_create_ext_req req_ext;

	req_ext.base = arg->req;
	req_ext.version = drm_vmw_gb_surface_v1;
	req_ext.svga3d_flags_upper_32_bits = 0;
	req_ext.multisample_pattern = SVGA3D_MS_PATTERN_NONE;
	req_ext.quality_level = SVGA3D_MS_QUALITY_NONE;
	req_ext.must_be_zero = 0;

	return vmw_gb_surface_define_internal(dev, &req_ext, rep, file_priv);
}