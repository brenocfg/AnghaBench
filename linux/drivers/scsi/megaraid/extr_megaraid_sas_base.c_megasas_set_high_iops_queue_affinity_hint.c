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
struct megasas_instance {scalar_t__ perf_mode; int low_latency_index_start; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MR_BALANCED_PERF_MODE ; 
 int /*<<< orphan*/  cpumask_of_node (int) ; 
 int dev_to_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_irq_vector (TYPE_1__*,int) ; 

__attribute__((used)) static inline void
megasas_set_high_iops_queue_affinity_hint(struct megasas_instance *instance)
{
	int i;
	int local_numa_node;

	if (instance->perf_mode == MR_BALANCED_PERF_MODE) {
		local_numa_node = dev_to_node(&instance->pdev->dev);

		for (i = 0; i < instance->low_latency_index_start; i++)
			irq_set_affinity_hint(pci_irq_vector(instance->pdev, i),
				cpumask_of_node(local_numa_node));
	}
}