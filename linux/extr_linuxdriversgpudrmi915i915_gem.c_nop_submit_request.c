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
struct i915_request {TYPE_2__ fence; TYPE_1__* engine; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_set_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_request_submit (struct i915_request*) ; 

__attribute__((used)) static void nop_submit_request(struct i915_request *request)
{
	GEM_TRACE("%s fence %llx:%d -> -EIO\n",
		  request->engine->name,
		  request->fence.context, request->fence.seqno);
	dma_fence_set_error(&request->fence, -EIO);

	i915_request_submit(request);
}