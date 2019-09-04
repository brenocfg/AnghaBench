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
struct i915_vma {int* exec_flags; } ;
struct i915_execbuffer {size_t buffer_count; int* flags; int /*<<< orphan*/ * vma; int /*<<< orphan*/  batch_len; int /*<<< orphan*/  batch_start_offset; TYPE_1__* batch; TYPE_2__* engine; } ;
struct drm_i915_gem_object {int* exec_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  batch_pool; } ;
struct TYPE_3__ {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int EACCES ; 
 struct i915_vma* ERR_CAST (struct i915_vma*) ; 
 struct i915_vma* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int /*<<< orphan*/  PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int __EXEC_OBJECT_HAS_PIN ; 
 int __EXEC_OBJECT_HAS_REF ; 
 struct i915_vma* i915_gem_batch_pool_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct i915_vma* i915_gem_object_ggtt_pin (struct i915_vma*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_pages (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_get (struct i915_vma*) ; 
 int intel_engine_cmd_parser (TYPE_2__*,int /*<<< orphan*/ ,struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct i915_vma *eb_parse(struct i915_execbuffer *eb, bool is_master)
{
	struct drm_i915_gem_object *shadow_batch_obj;
	struct i915_vma *vma;
	int err;

	shadow_batch_obj = i915_gem_batch_pool_get(&eb->engine->batch_pool,
						   PAGE_ALIGN(eb->batch_len));
	if (IS_ERR(shadow_batch_obj))
		return ERR_CAST(shadow_batch_obj);

	err = intel_engine_cmd_parser(eb->engine,
				      eb->batch->obj,
				      shadow_batch_obj,
				      eb->batch_start_offset,
				      eb->batch_len,
				      is_master);
	if (err) {
		if (err == -EACCES) /* unhandled chained batch */
			vma = NULL;
		else
			vma = ERR_PTR(err);
		goto out;
	}

	vma = i915_gem_object_ggtt_pin(shadow_batch_obj, NULL, 0, 0, 0);
	if (IS_ERR(vma))
		goto out;

	eb->vma[eb->buffer_count] = i915_vma_get(vma);
	eb->flags[eb->buffer_count] =
		__EXEC_OBJECT_HAS_PIN | __EXEC_OBJECT_HAS_REF;
	vma->exec_flags = &eb->flags[eb->buffer_count];
	eb->buffer_count++;

out:
	i915_gem_object_unpin_pages(shadow_batch_obj);
	return vma;
}