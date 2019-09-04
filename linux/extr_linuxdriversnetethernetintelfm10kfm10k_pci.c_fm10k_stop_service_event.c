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
 int /*<<< orphan*/  __FM10K_SERVICE_SCHED ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_stop_service_event(struct fm10k_intfc *interface)
{
	set_bit(__FM10K_SERVICE_DISABLE, interface->state);
	cancel_work_sync(&interface->service_task);

	/* It's possible that cancel_work_sync stopped the service task from
	 * running before it could actually start. In this case the
	 * __FM10K_SERVICE_SCHED bit will never be cleared. Since we know that
	 * the service task cannot be running at this point, we need to clear
	 * the scheduled bit, as otherwise the service task may never be
	 * restarted.
	 */
	clear_bit(__FM10K_SERVICE_SCHED, interface->state);
}