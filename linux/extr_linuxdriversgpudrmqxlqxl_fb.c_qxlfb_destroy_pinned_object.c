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
struct qxl_bo {int dummy; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct qxl_bo* gem_to_qxl_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  qxl_bo_kunmap (struct qxl_bo*) ; 
 int /*<<< orphan*/  qxl_bo_unpin (struct qxl_bo*) ; 

__attribute__((used)) static void qxlfb_destroy_pinned_object(struct drm_gem_object *gobj)
{
	struct qxl_bo *qbo = gem_to_qxl_bo(gobj);

	qxl_bo_kunmap(qbo);
	qxl_bo_unpin(qbo);

	drm_gem_object_put_unlocked(gobj);
}