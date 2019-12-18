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
struct TYPE_2__ {int /*<<< orphan*/  seqno; } ;
struct i915_request {TYPE_1__ fence; } ;
struct hang {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hws_seqno (struct hang*,struct i915_request*) ; 
 int /*<<< orphan*/  i915_seqno_passed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wait_for_us (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool wait_until_running(struct hang *h, struct i915_request *rq)
{
	return !(wait_for_us(i915_seqno_passed(hws_seqno(h, rq),
					       rq->fence.seqno),
			     10) &&
		 wait_for(i915_seqno_passed(hws_seqno(h, rq),
					    rq->fence.seqno),
			  1000));
}