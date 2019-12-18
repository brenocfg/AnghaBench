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
struct fm10k_intfc {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __FM10K_SERVICE_REQUEST ; 
 int /*<<< orphan*/  __FM10K_SERVICE_SCHED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_service_event_schedule (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_service_event_complete(struct fm10k_intfc *interface)
{
	WARN_ON(!test_bit(__FM10K_SERVICE_SCHED, interface->state));

	/* flush memory to make sure state is correct before next watchog */
	smp_mb__before_atomic();
	clear_bit(__FM10K_SERVICE_SCHED, interface->state);

	/* If a service event was requested since we started, immediately
	 * re-schedule now. This ensures we don't drop a request until the
	 * next timer event.
	 */
	if (test_bit(__FM10K_SERVICE_REQUEST, interface->state))
		fm10k_service_event_schedule(interface);
}