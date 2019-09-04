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
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct qxl_rect {scalar_t__ left; scalar_t__ top; scalar_t__ right; scalar_t__ bottom; } ;
struct qxl_device {int dummy; } ;
struct qxl_bo {int /*<<< orphan*/  surface_id; int /*<<< orphan*/  placement; int /*<<< orphan*/  tbo; int /*<<< orphan*/  type; int /*<<< orphan*/  pin_count; } ;
struct drm_qxl_update_area {scalar_t__ left; scalar_t__ top; scalar_t__ right; scalar_t__ bottom; int /*<<< orphan*/  handle; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct qxl_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOENT ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct qxl_bo* gem_to_qxl_bo (struct drm_gem_object*) ; 
 int qxl_bo_check_id (struct qxl_device*,struct qxl_bo*) ; 
 int qxl_bo_reserve (struct qxl_bo*,int) ; 
 int /*<<< orphan*/  qxl_bo_unreserve (struct qxl_bo*) ; 
 int qxl_io_update_area (struct qxl_device*,struct qxl_bo*,struct qxl_rect*) ; 
 int /*<<< orphan*/  qxl_ttm_placement_from_domain (struct qxl_bo*,int /*<<< orphan*/ ,int) ; 
 int ttm_bo_validate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ttm_operation_ctx*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int qxl_update_area_ioctl(struct drm_device *dev, void *data,
				 struct drm_file *file)
{
	struct qxl_device *qdev = dev->dev_private;
	struct drm_qxl_update_area *update_area = data;
	struct qxl_rect area = {.left = update_area->left,
				.top = update_area->top,
				.right = update_area->right,
				.bottom = update_area->bottom};
	int ret;
	struct drm_gem_object *gobj = NULL;
	struct qxl_bo *qobj = NULL;
	struct ttm_operation_ctx ctx = { true, false };

	if (update_area->left >= update_area->right ||
	    update_area->top >= update_area->bottom)
		return -EINVAL;

	gobj = drm_gem_object_lookup(file, update_area->handle);
	if (gobj == NULL)
		return -ENOENT;

	qobj = gem_to_qxl_bo(gobj);

	ret = qxl_bo_reserve(qobj, false);
	if (ret)
		goto out;

	if (!qobj->pin_count) {
		qxl_ttm_placement_from_domain(qobj, qobj->type, false);
		ret = ttm_bo_validate(&qobj->tbo, &qobj->placement, &ctx);
		if (unlikely(ret))
			goto out;
	}

	ret = qxl_bo_check_id(qdev, qobj);
	if (ret)
		goto out2;
	if (!qobj->surface_id)
		DRM_ERROR("got update area for surface with no id %d\n", update_area->handle);
	ret = qxl_io_update_area(qdev, qobj, &area);

out2:
	qxl_bo_unreserve(qobj);

out:
	drm_gem_object_put_unlocked(gobj);
	return ret;
}