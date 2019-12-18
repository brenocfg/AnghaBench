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
struct idle_inject_thread {scalar_t__ should_run; } ;
struct idle_inject_device {int /*<<< orphan*/  idle_duration_us; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idle_inject_device ; 
 int /*<<< orphan*/  idle_inject_thread ; 
 struct idle_inject_device* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 struct idle_inject_thread* per_cpu_ptr (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  play_idle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void idle_inject_fn(unsigned int cpu)
{
	struct idle_inject_device *ii_dev;
	struct idle_inject_thread *iit;

	ii_dev = per_cpu(idle_inject_device, cpu);
	iit = per_cpu_ptr(&idle_inject_thread, cpu);

	/*
	 * Let the smpboot main loop know that the task should not run again.
	 */
	iit->should_run = 0;

	play_idle(READ_ONCE(ii_dev->idle_duration_us));
}