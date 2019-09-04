#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i915_timeline {int /*<<< orphan*/  name; int /*<<< orphan*/  last_request; } ;
struct intel_engine_cs {int /*<<< orphan*/  name; TYPE_2__* i915; struct i915_timeline timeline; } ;
struct TYPE_6__ {int /*<<< orphan*/  seqno; int /*<<< orphan*/  context; } ;
struct i915_request {struct i915_timeline* timeline; TYPE_3__ fence; struct intel_engine_cs* engine; } ;
struct TYPE_4__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_5__ {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i915_request* i915_gem_active_raw (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct i915_request *
last_request_on_engine(struct i915_timeline *timeline,
		       struct intel_engine_cs *engine)
{
	struct i915_request *rq;

	GEM_BUG_ON(timeline == &engine->timeline);

	rq = i915_gem_active_raw(&timeline->last_request,
				 &engine->i915->drm.struct_mutex);
	if (rq && rq->engine == engine) {
		GEM_TRACE("last request for %s on engine %s: %llx:%d\n",
			  timeline->name, engine->name,
			  rq->fence.context, rq->fence.seqno);
		GEM_BUG_ON(rq->timeline != timeline);
		return rq;
	}

	return NULL;
}