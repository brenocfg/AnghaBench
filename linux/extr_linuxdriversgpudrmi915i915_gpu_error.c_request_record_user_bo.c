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
struct i915_request {int /*<<< orphan*/  i915; struct i915_capture_list* capture_list; } ;
struct i915_capture_list {int /*<<< orphan*/  vma; struct i915_capture_list* next; } ;
struct drm_i915_error_object {int dummy; } ;
struct drm_i915_error_engine {long user_bo_count; struct drm_i915_error_object** user_bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct drm_i915_error_object* i915_error_object_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_i915_error_object** kcalloc (long,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void request_record_user_bo(struct i915_request *request,
				   struct drm_i915_error_engine *ee)
{
	struct i915_capture_list *c;
	struct drm_i915_error_object **bo;
	long count;

	count = 0;
	for (c = request->capture_list; c; c = c->next)
		count++;

	bo = NULL;
	if (count)
		bo = kcalloc(count, sizeof(*bo), GFP_ATOMIC);
	if (!bo)
		return;

	count = 0;
	for (c = request->capture_list; c; c = c->next) {
		bo[count] = i915_error_object_create(request->i915, c->vma);
		if (!bo[count])
			break;
		count++;
	}

	ee->user_bo = bo;
	ee->user_bo_count = count;
}