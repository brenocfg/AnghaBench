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
typedef  int /*<<< orphan*/  u32 ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int /*<<< orphan*/  table_lock; int /*<<< orphan*/  object_idr; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR_OR_NULL (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_object_release_handle (int /*<<< orphan*/ ,struct drm_gem_object*,struct drm_file*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct drm_gem_object* idr_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int
drm_gem_handle_delete(struct drm_file *filp, u32 handle)
{
	struct drm_gem_object *obj;

	spin_lock(&filp->table_lock);

	/* Check if we currently have a reference on the object */
	obj = idr_replace(&filp->object_idr, NULL, handle);
	spin_unlock(&filp->table_lock);
	if (IS_ERR_OR_NULL(obj))
		return -EINVAL;

	/* Release driver's reference and decrement refcount. */
	drm_gem_object_release_handle(handle, obj, filp);

	/* And finally make the handle available for future allocations. */
	spin_lock(&filp->table_lock);
	idr_remove(&filp->object_idr, handle);
	spin_unlock(&filp->table_lock);

	return 0;
}