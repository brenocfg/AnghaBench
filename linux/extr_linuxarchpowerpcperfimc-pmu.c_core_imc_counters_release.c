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
struct perf_event {int cpu; } ;
struct imc_pmu_ref {scalar_t__ refc; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_IMC_COUNTERS_CORE ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 struct imc_pmu_ref* core_imc_refc ; 
 int /*<<< orphan*/  get_hard_smp_processor_id (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int opal_imc_counters_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int threads_per_core ; 

__attribute__((used)) static void core_imc_counters_release(struct perf_event *event)
{
	int rc, core_id;
	struct imc_pmu_ref *ref;

	if (event->cpu < 0)
		return;
	/*
	 * See if we need to disable the IMC PMU.
	 * If no events are currently in use, then we have to take a
	 * mutex to ensure that we don't race with another task doing
	 * enable or disable the core counters.
	 */
	core_id = event->cpu / threads_per_core;

	/* Take the mutex lock and decrement the refernce count for this core */
	ref = &core_imc_refc[core_id];
	if (!ref)
		return;

	mutex_lock(&ref->lock);
	if (ref->refc == 0) {
		/*
		 * The scenario where this is true is, when perf session is
		 * started, followed by offlining of all cpus in a given core.
		 *
		 * In the cpuhotplug offline path, ppc_core_imc_cpu_offline()
		 * function set the ref->count to zero, if the cpu which is
		 * about to offline is the last cpu in a given core and make
		 * an OPAL call to disable the engine in that core.
		 *
		 */
		mutex_unlock(&ref->lock);
		return;
	}
	ref->refc--;
	if (ref->refc == 0) {
		rc = opal_imc_counters_stop(OPAL_IMC_COUNTERS_CORE,
					    get_hard_smp_processor_id(event->cpu));
		if (rc) {
			mutex_unlock(&ref->lock);
			pr_err("IMC: Unable to stop the counters for core %d\n", core_id);
			return;
		}
	} else if (ref->refc < 0) {
		WARN(1, "core-imc: Invalid event reference count\n");
		ref->refc = 0;
	}
	mutex_unlock(&ref->lock);
}