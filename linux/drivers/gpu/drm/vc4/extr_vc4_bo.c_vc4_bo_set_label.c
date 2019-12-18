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
struct vc4_dev {TYPE_1__* bo_labels; int /*<<< orphan*/  bo_lock; } ;
struct vc4_bo {size_t label; } ;
struct drm_gem_object {scalar_t__ size; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ num_allocated; int /*<<< orphan*/ * name; int /*<<< orphan*/  size_allocated; } ;

/* Variables and functions */
 scalar_t__ is_user_label (size_t) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct vc4_bo* to_vc4_bo (struct drm_gem_object*) ; 
 struct vc4_dev* to_vc4_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vc4_bo_set_label(struct drm_gem_object *gem_obj, int label)
{
	struct vc4_bo *bo = to_vc4_bo(gem_obj);
	struct vc4_dev *vc4 = to_vc4_dev(gem_obj->dev);

	lockdep_assert_held(&vc4->bo_lock);

	if (label != -1) {
		vc4->bo_labels[label].num_allocated++;
		vc4->bo_labels[label].size_allocated += gem_obj->size;
	}

	vc4->bo_labels[bo->label].num_allocated--;
	vc4->bo_labels[bo->label].size_allocated -= gem_obj->size;

	if (vc4->bo_labels[bo->label].num_allocated == 0 &&
	    is_user_label(bo->label)) {
		/* Free user BO label slots on last unreference.
		 * Slots are just where we track the stats for a given
		 * name, and once a name is unused we can reuse that
		 * slot.
		 */
		kfree(vc4->bo_labels[bo->label].name);
		vc4->bo_labels[bo->label].name = NULL;
	}

	bo->label = label;
}