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
typedef  int u32 ;
struct i915_request {int global_seqno; TYPE_3__* engine; } ;
struct TYPE_5__ {int* wait; } ;
struct TYPE_4__ {TYPE_2__ mbox; } ;
struct TYPE_6__ {size_t hw_id; TYPE_1__ semaphore; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int*) ; 
 int /*<<< orphan*/  MI_NOOP ; 
 int MI_SEMAPHORE_COMPARE ; 
 int MI_SEMAPHORE_MBOX ; 
 int MI_SEMAPHORE_REGISTER ; 
 int MI_SEMAPHORE_SYNC_INVALID ; 
 int PTR_ERR (int*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,int*) ; 
 int* intel_ring_begin (struct i915_request*,int) ; 

__attribute__((used)) static int
gen6_ring_sync_to(struct i915_request *rq, struct i915_request *signal)
{
	u32 dw1 = MI_SEMAPHORE_MBOX |
		  MI_SEMAPHORE_COMPARE |
		  MI_SEMAPHORE_REGISTER;
	u32 wait_mbox = signal->engine->semaphore.mbox.wait[rq->engine->hw_id];
	u32 *cs;

	WARN_ON(wait_mbox == MI_SEMAPHORE_SYNC_INVALID);

	cs = intel_ring_begin(rq, 4);
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	*cs++ = dw1 | wait_mbox;
	/* Throughout all of the GEM code, seqno passed implies our current
	 * seqno is >= the last seqno executed. However for hardware the
	 * comparison is strictly greater than.
	 */
	*cs++ = signal->global_seqno - 1;
	*cs++ = 0;
	*cs++ = MI_NOOP;
	intel_ring_advance(rq, cs);

	return 0;
}