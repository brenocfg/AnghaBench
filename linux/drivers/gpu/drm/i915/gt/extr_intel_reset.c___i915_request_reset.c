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
struct TYPE_4__ {int /*<<< orphan*/  seqno; int /*<<< orphan*/  context; } ;
struct i915_request {int /*<<< orphan*/  gem_context; TYPE_2__ fence; TYPE_1__* engine; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ context_mark_guilty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_mark_innocent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_set_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  engine_skip_context (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_completed (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_skip (struct i915_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yesno (int) ; 

void __i915_request_reset(struct i915_request *rq, bool guilty)
{
	GEM_TRACE("%s rq=%llx:%lld, guilty? %s\n",
		  rq->engine->name,
		  rq->fence.context,
		  rq->fence.seqno,
		  yesno(guilty));

	GEM_BUG_ON(i915_request_completed(rq));

	if (guilty) {
		i915_request_skip(rq, -EIO);
		if (context_mark_guilty(rq->gem_context))
			engine_skip_context(rq);
	} else {
		dma_fence_set_error(&rq->fence, -EAGAIN);
		context_mark_innocent(rq->gem_context);
	}
}