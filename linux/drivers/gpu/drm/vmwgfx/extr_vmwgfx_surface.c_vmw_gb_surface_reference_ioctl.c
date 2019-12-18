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
struct drm_vmw_gb_surface_ref_rep {int /*<<< orphan*/  crep; int /*<<< orphan*/  creq; } ;
struct drm_vmw_surface_arg {int dummy; } ;
union drm_vmw_gb_surface_reference_arg {struct drm_vmw_gb_surface_ref_rep rep; struct drm_vmw_surface_arg req; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct drm_vmw_gb_surface_ref_ext_rep {int /*<<< orphan*/  crep; TYPE_1__ creq; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 
 int vmw_gb_surface_reference_internal (struct drm_device*,struct drm_vmw_surface_arg*,struct drm_vmw_gb_surface_ref_ext_rep*,struct drm_file*) ; 

int vmw_gb_surface_reference_ioctl(struct drm_device *dev, void *data,
				   struct drm_file *file_priv)
{
	union drm_vmw_gb_surface_reference_arg *arg =
	    (union drm_vmw_gb_surface_reference_arg *)data;
	struct drm_vmw_surface_arg *req = &arg->req;
	struct drm_vmw_gb_surface_ref_rep *rep = &arg->rep;
	struct drm_vmw_gb_surface_ref_ext_rep rep_ext;
	int ret;

	ret = vmw_gb_surface_reference_internal(dev, req, &rep_ext, file_priv);

	if (unlikely(ret != 0))
		return ret;

	rep->creq = rep_ext.creq.base;
	rep->crep = rep_ext.crep;

	return ret;
}