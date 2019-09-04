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
struct ttm_object_file {int dummy; } ;
struct drm_vmw_shader_arg {int /*<<< orphan*/  handle; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {struct ttm_object_file* tfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_REF_USAGE ; 
 int ttm_ref_object_base_unref (struct ttm_object_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* vmw_fpriv (struct drm_file*) ; 

int vmw_shader_destroy_ioctl(struct drm_device *dev, void *data,
			      struct drm_file *file_priv)
{
	struct drm_vmw_shader_arg *arg = (struct drm_vmw_shader_arg *)data;
	struct ttm_object_file *tfile = vmw_fpriv(file_priv)->tfile;

	return ttm_ref_object_base_unref(tfile, arg->handle,
					 TTM_REF_USAGE);
}