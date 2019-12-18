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
struct fm10k_intfc {int /*<<< orphan*/  state; int /*<<< orphan*/  service_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  __FM10K_SERVICE_DISABLE ; 
 int /*<<< orphan*/  __FM10K_SERVICE_REQUEST ; 
 int /*<<< orphan*/  __FM10K_SERVICE_SCHED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_workqueue ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fm10k_service_event_schedule(struct fm10k_intfc *interface)
{
	if (!test_bit(__FM10K_SERVICE_DISABLE, interface->state) &&
	    !test_and_set_bit(__FM10K_SERVICE_SCHED, interface->state)) {
		clear_bit(__FM10K_SERVICE_REQUEST, interface->state);
		queue_work(fm10k_workqueue, &interface->service_task);
	} else {
		set_bit(__FM10K_SERVICE_REQUEST, interface->state);
	}
}