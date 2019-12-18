#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* mm; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_gem_object {TYPE_3__ userptr; TYPE_1__ base; } ;
struct TYPE_8__ {int /*<<< orphan*/  mm_lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  __i915_mm_struct_free ; 
 int /*<<< orphan*/  kref_put_mutex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
i915_gem_userptr_release__mm_struct(struct drm_i915_gem_object *obj)
{
	if (obj->userptr.mm == NULL)
		return;

	kref_put_mutex(&obj->userptr.mm->kref,
		       __i915_mm_struct_free,
		       &to_i915(obj->base.dev)->mm_lock);
	obj->userptr.mm = NULL;
}