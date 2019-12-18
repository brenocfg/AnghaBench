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

/* Variables and functions */
 int /*<<< orphan*/  PROFILE_MUNMAP ; 
 int /*<<< orphan*/  PROFILE_TASK_EXIT ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  end_cpu_work () ; 
 int /*<<< orphan*/  flush_cpu_work () ; 
 int /*<<< orphan*/  free_all_tasks () ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  marked_cpus ; 
 int /*<<< orphan*/  module_load_nb ; 
 int /*<<< orphan*/  munmap_nb ; 
 int /*<<< orphan*/  profile_event_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_exit_nb ; 
 int /*<<< orphan*/  task_free_nb ; 
 int /*<<< orphan*/  task_handoff_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_module_notifier (int /*<<< orphan*/ *) ; 

void sync_stop(void)
{
	end_cpu_work();
	unregister_module_notifier(&module_load_nb);
	profile_event_unregister(PROFILE_MUNMAP, &munmap_nb);
	profile_event_unregister(PROFILE_TASK_EXIT, &task_exit_nb);
	task_handoff_unregister(&task_free_nb);
	barrier();			/* do all of the above first */

	flush_cpu_work();

	free_all_tasks();
	free_cpumask_var(marked_cpus);
}