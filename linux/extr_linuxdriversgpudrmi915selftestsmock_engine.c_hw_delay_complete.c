#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timer_list {int dummy; } ;
struct mock_request {scalar_t__ delay; } ;
struct mock_engine {int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  hw_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  advance (struct mock_engine*,struct mock_request*) ; 
 struct mock_engine* engine ; 
 struct mock_request* first_request (struct mock_engine*) ; 
 struct mock_engine* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_delay ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hw_delay_complete(struct timer_list *t)
{
	struct mock_engine *engine = from_timer(engine, t, hw_delay);
	struct mock_request *request;

	spin_lock(&engine->hw_lock);

	/* Timer fired, first request is complete */
	request = first_request(engine);
	if (request)
		advance(engine, request);

	/*
	 * Also immediately signal any subsequent 0-delay requests, but
	 * requeue the timer for the next delayed request.
	 */
	while ((request = first_request(engine))) {
		if (request->delay) {
			mod_timer(&engine->hw_delay, jiffies + request->delay);
			break;
		}

		advance(engine, request);
	}

	spin_unlock(&engine->hw_lock);
}