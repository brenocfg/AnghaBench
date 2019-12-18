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
struct drm_vmw_gb_surface_create_ext_req {int dummy; } ;
union drm_vmw_gb_surface_create_ext_arg {struct drm_vmw_gb_surface_create_rep rep; struct drm_vmw_gb_surface_create_ext_req req; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int vmw_gb_surface_define_internal (struct drm_device*,struct drm_vmw_gb_surface_create_ext_req*,struct drm_vmw_gb_surface_create_rep*,struct drm_file*) ; 

int vmw_gb_surface_define_ext_ioctl(struct drm_device *dev, void *data,
				struct drm_file *file_priv)
{
	union drm_vmw_gb_surface_create_ext_arg *arg =
	    (union drm_vmw_gb_surface_create_ext_arg *)data;
	struct drm_vmw_gb_surface_create_ext_req *req = &arg->req;
	struct drm_vmw_gb_surface_create_rep *rep = &arg->rep;

	return vmw_gb_surface_define_internal(dev, req, rep, file_priv);
}