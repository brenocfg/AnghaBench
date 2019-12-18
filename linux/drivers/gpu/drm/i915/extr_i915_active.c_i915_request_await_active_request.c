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
struct i915_request {int /*<<< orphan*/  fence; TYPE_2__* i915; } ;
struct i915_active_request {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_4__ {TYPE_1__ drm; } ;

/* Variables and functions */
 struct i915_request* i915_active_request_raw (struct i915_active_request*,int /*<<< orphan*/ *) ; 
 int i915_request_await_dma_fence (struct i915_request*,int /*<<< orphan*/ *) ; 

int i915_request_await_active_request(struct i915_request *rq,
				      struct i915_active_request *active)
{
	struct i915_request *barrier =
		i915_active_request_raw(active, &rq->i915->drm.struct_mutex);

	return barrier ? i915_request_await_dma_fence(rq, &barrier->fence) : 0;
}