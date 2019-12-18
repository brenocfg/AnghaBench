#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct list_head {int dummy; } ;
struct i915_gem_context {TYPE_2__* i915; int /*<<< orphan*/  vm; } ;
struct i915_address_space {int total; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  st_link; } ;
struct drm_file {int dummy; } ;
struct TYPE_4__ {struct i915_address_space vm; } ;
struct TYPE_5__ {TYPE_1__ ggtt; } ;

/* Variables and functions */
 unsigned long long DW_PER_PAGE ; 
 struct drm_i915_gem_object* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct drm_i915_gem_object*) ; 
 unsigned long long PAGE_SIZE ; 
 int /*<<< orphan*/  STACK_MAGIC ; 
 int cpu_fill (struct drm_i915_gem_object*,int /*<<< orphan*/ ) ; 
 int file_add_object (struct drm_file*,struct drm_i915_gem_object*) ; 
 struct drm_i915_gem_object* huge_gem_object (TYPE_2__*,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_retire_requests (TYPE_2__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  min (int,unsigned long long) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  round_down (int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static struct drm_i915_gem_object *
create_test_object(struct i915_gem_context *ctx,
		   struct drm_file *file,
		   struct list_head *objects)
{
	struct drm_i915_gem_object *obj;
	struct i915_address_space *vm = ctx->vm ?: &ctx->i915->ggtt.vm;
	u64 size;
	int err;

	/* Keep in GEM's good graces */
	i915_retire_requests(ctx->i915);

	size = min(vm->total / 2, 1024ull * DW_PER_PAGE * PAGE_SIZE);
	size = round_down(size, DW_PER_PAGE * PAGE_SIZE);

	obj = huge_gem_object(ctx->i915, DW_PER_PAGE * PAGE_SIZE, size);
	if (IS_ERR(obj))
		return obj;

	err = file_add_object(file, obj);
	i915_gem_object_put(obj);
	if (err)
		return ERR_PTR(err);

	err = cpu_fill(obj, STACK_MAGIC);
	if (err) {
		pr_err("Failed to fill object with cpu, err=%d\n",
		       err);
		return ERR_PTR(err);
	}

	list_add_tail(&obj->st_link, objects);
	return obj;
}