#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spinner {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  seqno; } ;
struct i915_request {TYPE_1__ fence; int /*<<< orphan*/  global_seqno; int /*<<< orphan*/  execute; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hws_seqno (struct spinner*,struct i915_request*) ; 
 int /*<<< orphan*/  i915_seqno_passed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wait_for_us (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool wait_for_spinner(struct spinner *spin, struct i915_request *rq)
{
	if (!wait_event_timeout(rq->execute,
				READ_ONCE(rq->global_seqno),
				msecs_to_jiffies(10)))
		return false;

	return !(wait_for_us(i915_seqno_passed(hws_seqno(spin, rq),
					       rq->fence.seqno),
			     10) &&
		 wait_for(i915_seqno_passed(hws_seqno(spin, rq),
					    rq->fence.seqno),
			  1000));
}