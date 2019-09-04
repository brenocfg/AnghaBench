#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i915_vma {int /*<<< orphan*/ * exec_flags; struct drm_i915_gem_object* obj; } ;
struct i915_execbuffer {unsigned int buffer_count; unsigned int* flags; int /*<<< orphan*/  i915; int /*<<< orphan*/ * exec; TYPE_1__* request; struct i915_vma** vma; } ;
struct i915_capture_list {struct i915_vma* vma; struct i915_capture_list* next; } ;
struct drm_i915_gem_object {unsigned int cache_dirty; unsigned int cache_coherent; } ;
struct TYPE_4__ {struct i915_capture_list* capture_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int EXEC_OBJECT_ASYNC ; 
 unsigned int EXEC_OBJECT_CAPTURE ; 
 unsigned int EXEC_OBJECT_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int __EXEC_OBJECT_HAS_REF ; 
 int /*<<< orphan*/  __eb_unreserve_vma (struct i915_vma*,unsigned int) ; 
 int /*<<< orphan*/  i915_gem_chipset_flush (int /*<<< orphan*/ ) ; 
 scalar_t__ i915_gem_clflush_object (struct drm_i915_gem_object*,int /*<<< orphan*/ ) ; 
 int i915_request_await_object (TYPE_1__*,struct drm_i915_gem_object*,unsigned int) ; 
 int /*<<< orphan*/  i915_request_skip (TYPE_1__*,int) ; 
 int i915_vma_move_to_active (struct i915_vma*,TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  i915_vma_put (struct i915_vma*) ; 
 struct i915_capture_list* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static int eb_move_to_gpu(struct i915_execbuffer *eb)
{
	const unsigned int count = eb->buffer_count;
	unsigned int i;
	int err;

	for (i = 0; i < count; i++) {
		unsigned int flags = eb->flags[i];
		struct i915_vma *vma = eb->vma[i];
		struct drm_i915_gem_object *obj = vma->obj;

		if (flags & EXEC_OBJECT_CAPTURE) {
			struct i915_capture_list *capture;

			capture = kmalloc(sizeof(*capture), GFP_KERNEL);
			if (unlikely(!capture))
				return -ENOMEM;

			capture->next = eb->request->capture_list;
			capture->vma = eb->vma[i];
			eb->request->capture_list = capture;
		}

		/*
		 * If the GPU is not _reading_ through the CPU cache, we need
		 * to make sure that any writes (both previous GPU writes from
		 * before a change in snooping levels and normal CPU writes)
		 * caught in that cache are flushed to main memory.
		 *
		 * We want to say
		 *   obj->cache_dirty &&
		 *   !(obj->cache_coherent & I915_BO_CACHE_COHERENT_FOR_READ)
		 * but gcc's optimiser doesn't handle that as well and emits
		 * two jumps instead of one. Maybe one day...
		 */
		if (unlikely(obj->cache_dirty & ~obj->cache_coherent)) {
			if (i915_gem_clflush_object(obj, 0))
				flags &= ~EXEC_OBJECT_ASYNC;
		}

		if (flags & EXEC_OBJECT_ASYNC)
			continue;

		err = i915_request_await_object
			(eb->request, obj, flags & EXEC_OBJECT_WRITE);
		if (err)
			return err;
	}

	for (i = 0; i < count; i++) {
		unsigned int flags = eb->flags[i];
		struct i915_vma *vma = eb->vma[i];

		err = i915_vma_move_to_active(vma, eb->request, flags);
		if (unlikely(err)) {
			i915_request_skip(eb->request, err);
			return err;
		}

		__eb_unreserve_vma(vma, flags);
		vma->exec_flags = NULL;

		if (unlikely(flags & __EXEC_OBJECT_HAS_REF))
			i915_vma_put(vma);
	}
	eb->exec = NULL;

	/* Unconditionally flush any chipset caches (for streaming writes). */
	i915_gem_chipset_flush(eb->i915);

	return 0;
}