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
struct timer_list {int dummy; } ;
struct mock_engine {int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  hw_delay; } ;
struct TYPE_2__ {scalar_t__ delay; } ;
struct i915_request {TYPE_1__ mock; } ;

/* Variables and functions */
 int /*<<< orphan*/  advance (struct i915_request*) ; 
 struct mock_engine* engine ; 
 struct i915_request* first_request (struct mock_engine*) ; 
 struct mock_engine* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_delay ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void hw_delay_complete(struct timer_list *t)
{
	struct mock_engine *engine = from_timer(engine, t, hw_delay);
	struct i915_request *request;
	unsigned long flags;

	spin_lock_irqsave(&engine->hw_lock, flags);

	/* Timer fired, first request is complete */
	request = first_request(engine);
	if (request)
		advance(request);

	/*
	 * Also immediately signal any subsequent 0-delay requests, but
	 * requeue the timer for the next delayed request.
	 */
	while ((request = first_request(engine))) {
		if (request->mock.delay) {
			mod_timer(&engine->hw_delay,
				  jiffies + request->mock.delay);
			break;
		}

		advance(request);
	}

	spin_unlock_irqrestore(&engine->hw_lock, flags);
}