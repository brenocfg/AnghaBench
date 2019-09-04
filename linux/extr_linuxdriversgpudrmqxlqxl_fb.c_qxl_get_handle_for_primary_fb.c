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
typedef  int /*<<< orphan*/  uint32_t ;
struct qxl_device {TYPE_1__* fbdev_qfb; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct TYPE_2__ {struct drm_gem_object* obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int drm_gem_handle_create (struct drm_file*,struct drm_gem_object*,int /*<<< orphan*/ *) ; 

int qxl_get_handle_for_primary_fb(struct qxl_device *qdev,
				  struct drm_file *file_priv,
				  uint32_t *handle)
{
	int r;
	struct drm_gem_object *gobj = qdev->fbdev_qfb->obj;

	BUG_ON(!gobj);
	/* drm_get_handle_create adds a reference - good */
	r = drm_gem_handle_create(file_priv, gobj, handle);
	if (r)
		return r;
	return 0;
}