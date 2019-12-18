#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  function; } ;
struct tx2_uncore_pmu {int cpu; int name; TYPE_1__ pmu; int /*<<< orphan*/  dev; int /*<<< orphan*/  entry; int /*<<< orphan*/  hpnode; TYPE_2__ hrtimer; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  CPUHP_AP_PERF_ARM_CAVIUM_TX2_UNCORE_ONLINE ; 
 int ENODEV ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int cpuhp_state_add_instance (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cpumask_any_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx2_hrtimer_callback ; 
 int /*<<< orphan*/  tx2_pmus ; 
 int tx2_uncore_pmu_register (struct tx2_uncore_pmu*) ; 

__attribute__((used)) static int tx2_uncore_pmu_add_dev(struct tx2_uncore_pmu *tx2_pmu)
{
	int ret, cpu;

	cpu = cpumask_any_and(cpumask_of_node(tx2_pmu->node),
			cpu_online_mask);

	tx2_pmu->cpu = cpu;
	hrtimer_init(&tx2_pmu->hrtimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	tx2_pmu->hrtimer.function = tx2_hrtimer_callback;

	ret = tx2_uncore_pmu_register(tx2_pmu);
	if (ret) {
		dev_err(tx2_pmu->dev, "%s PMU: Failed to init driver\n",
				tx2_pmu->name);
		return -ENODEV;
	}

	/* register hotplug callback for the pmu */
	ret = cpuhp_state_add_instance(
			CPUHP_AP_PERF_ARM_CAVIUM_TX2_UNCORE_ONLINE,
			&tx2_pmu->hpnode);
	if (ret) {
		dev_err(tx2_pmu->dev, "Error %d registering hotplug", ret);
		return ret;
	}

	/* Add to list */
	list_add(&tx2_pmu->entry, &tx2_pmus);

	dev_dbg(tx2_pmu->dev, "%s PMU UNCORE registered\n",
			tx2_pmu->pmu.name);
	return ret;
}