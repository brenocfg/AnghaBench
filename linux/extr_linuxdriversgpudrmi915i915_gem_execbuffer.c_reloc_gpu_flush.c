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
typedef  int /*<<< orphan*/  u32 ;
struct reloc_cache {int rq_size; TYPE_3__* rq; int /*<<< orphan*/ * rq_cmd; } ;
struct TYPE_5__ {int size; } ;
struct TYPE_8__ {TYPE_1__ base; } ;
struct TYPE_7__ {int /*<<< orphan*/  i915; TYPE_2__* batch; } ;
struct TYPE_6__ {TYPE_4__* obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  MI_BATCH_BUFFER_END ; 
 int /*<<< orphan*/  i915_gem_chipset_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (TYPE_4__*) ; 
 int /*<<< orphan*/  i915_request_add (TYPE_3__*) ; 

__attribute__((used)) static void reloc_gpu_flush(struct reloc_cache *cache)
{
	GEM_BUG_ON(cache->rq_size >= cache->rq->batch->obj->base.size / sizeof(u32));
	cache->rq_cmd[cache->rq_size] = MI_BATCH_BUFFER_END;
	i915_gem_object_unpin_map(cache->rq->batch->obj);
	i915_gem_chipset_flush(cache->rq->i915);

	i915_request_add(cache->rq);
	cache->rq = NULL;
}