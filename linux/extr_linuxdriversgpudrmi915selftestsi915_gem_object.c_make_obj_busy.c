#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i915_vma {int dummy; } ;
typedef  struct i915_vma i915_request ;
struct TYPE_4__ {int /*<<< orphan*/  vm; } ;
struct drm_i915_private {int /*<<< orphan*/  kernel_context; int /*<<< orphan*/ * engine; TYPE_2__ ggtt; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_OBJECT_WRITE ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int /*<<< orphan*/  PIN_USER ; 
 int PTR_ERR (struct i915_vma*) ; 
 size_t RCS ; 
 int /*<<< orphan*/  __i915_gem_object_release_unless_active (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_request_add (struct i915_vma*) ; 
 struct i915_vma* i915_request_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i915_vma* i915_vma_instance (struct drm_i915_gem_object*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int i915_vma_move_to_active (struct i915_vma*,struct i915_vma*,int /*<<< orphan*/ ) ; 
 int i915_vma_pin (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int make_obj_busy(struct drm_i915_gem_object *obj)
{
	struct drm_i915_private *i915 = to_i915(obj->base.dev);
	struct i915_request *rq;
	struct i915_vma *vma;
	int err;

	vma = i915_vma_instance(obj, &i915->ggtt.vm, NULL);
	if (IS_ERR(vma))
		return PTR_ERR(vma);

	err = i915_vma_pin(vma, 0, 0, PIN_USER);
	if (err)
		return err;

	rq = i915_request_alloc(i915->engine[RCS], i915->kernel_context);
	if (IS_ERR(rq)) {
		i915_vma_unpin(vma);
		return PTR_ERR(rq);
	}

	err = i915_vma_move_to_active(vma, rq, EXEC_OBJECT_WRITE);

	i915_request_add(rq);

	__i915_gem_object_release_unless_active(obj);
	i915_vma_unpin(vma);

	return err;
}