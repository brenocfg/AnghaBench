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
typedef  int /*<<< orphan*/  uint64_t ;
struct qxl_release {int dummy; } ;
struct qxl_bo {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct qxl_bo* gem_to_qxl_bo (struct drm_gem_object*) ; 
 int qxl_release_list_add (struct qxl_release*,struct qxl_bo*) ; 

__attribute__((used)) static int qxlhw_handle_to_bo(struct drm_file *file_priv, uint64_t handle,
			      struct qxl_release *release, struct qxl_bo **qbo_p)
{
	struct drm_gem_object *gobj;
	struct qxl_bo *qobj;
	int ret;

	gobj = drm_gem_object_lookup(file_priv, handle);
	if (!gobj)
		return -EINVAL;

	qobj = gem_to_qxl_bo(gobj);

	ret = qxl_release_list_add(release, qobj);
	drm_gem_object_put_unlocked(gobj);
	if (ret)
		return ret;

	*qbo_p = qobj;
	return 0;
}