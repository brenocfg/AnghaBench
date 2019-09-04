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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct qxl_surface {int dummy; } ;
struct qxl_device {int dummy; } ;
struct qxl_bo {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int drm_gem_handle_create (struct drm_file*,struct drm_gem_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct qxl_bo* gem_to_qxl_bo (struct drm_gem_object*) ; 
 int qxl_gem_object_create (struct qxl_device*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct qxl_surface*,struct drm_gem_object**) ; 

int qxl_gem_object_create_with_handle(struct qxl_device *qdev,
				      struct drm_file *file_priv,
				      u32 domain,
				      size_t size,
				      struct qxl_surface *surf,
				      struct qxl_bo **qobj,
				      uint32_t *handle)
{
	struct drm_gem_object *gobj;
	int r;

	BUG_ON(!qobj);
	BUG_ON(!handle);

	r = qxl_gem_object_create(qdev, size, 0,
				  domain,
				  false, false, surf,
				  &gobj);
	if (r)
		return -ENOMEM;
	r = drm_gem_handle_create(file_priv, gobj, handle);
	if (r)
		return r;
	/* drop reference from allocate - handle holds it now */
	*qobj = gem_to_qxl_bo(gobj);
	drm_gem_object_put_unlocked(gobj);
	return 0;
}