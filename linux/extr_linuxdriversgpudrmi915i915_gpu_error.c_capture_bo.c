#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  start; } ;
struct i915_vma {TYPE_3__* fence; TYPE_2__ node; struct drm_i915_gem_object* obj; } ;
struct TYPE_10__ {int /*<<< orphan*/ * mm; } ;
struct TYPE_9__ {scalar_t__ madv; int /*<<< orphan*/  dirty; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  size; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  cache_level; TYPE_5__ userptr; TYPE_4__ mm; int /*<<< orphan*/  write_domain; int /*<<< orphan*/  read_domains; int /*<<< orphan*/  frontbuffer_write; TYPE_1__ base; } ;
struct drm_i915_error_buffer {int fence_reg; int purgeable; int /*<<< orphan*/  cache_level; int /*<<< orphan*/  userptr; int /*<<< orphan*/  dirty; int /*<<< orphan*/  tiling; int /*<<< orphan*/  write_domain; int /*<<< orphan*/  read_domains; int /*<<< orphan*/  gtt_offset; int /*<<< orphan*/  engine; int /*<<< orphan*/  wseqno; int /*<<< orphan*/  name; int /*<<< orphan*/  size; } ;
struct TYPE_8__ {int id; } ;

/* Variables and functions */
 scalar_t__ I915_MADV_WILLNEED ; 
 int /*<<< orphan*/  __active_get_engine_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __active_get_seqno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_get_tiling (struct drm_i915_gem_object*) ; 

__attribute__((used)) static void capture_bo(struct drm_i915_error_buffer *err,
		       struct i915_vma *vma)
{
	struct drm_i915_gem_object *obj = vma->obj;

	err->size = obj->base.size;
	err->name = obj->base.name;

	err->wseqno = __active_get_seqno(&obj->frontbuffer_write);
	err->engine = __active_get_engine_id(&obj->frontbuffer_write);

	err->gtt_offset = vma->node.start;
	err->read_domains = obj->read_domains;
	err->write_domain = obj->write_domain;
	err->fence_reg = vma->fence ? vma->fence->id : -1;
	err->tiling = i915_gem_object_get_tiling(obj);
	err->dirty = obj->mm.dirty;
	err->purgeable = obj->mm.madv != I915_MADV_WILLNEED;
	err->userptr = obj->userptr.mm != NULL;
	err->cache_level = obj->cache_level;
}