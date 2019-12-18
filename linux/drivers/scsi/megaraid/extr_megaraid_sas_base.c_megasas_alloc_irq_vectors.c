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
struct megasas_instance {scalar_t__ perf_mode; int msix_vectors; int low_latency_index_start; scalar_t__ smp_affinity_enable; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MR_BALANCED_PERF_MODE ; 
 scalar_t__ MR_LATENCY_PERF_MODE ; 
 int __megasas_alloc_irq_vectors (struct megasas_instance*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  megasas_set_high_iops_queue_affinity_hint (struct megasas_instance*) ; 
 int min (unsigned int,int) ; 
 unsigned int num_online_cpus () ; 
 int /*<<< orphan*/  pci_free_irq_vectors (TYPE_1__*) ; 

__attribute__((used)) static void
megasas_alloc_irq_vectors(struct megasas_instance *instance)
{
	int i;
	unsigned int num_msix_req;

	i = __megasas_alloc_irq_vectors(instance);

	if ((instance->perf_mode == MR_BALANCED_PERF_MODE) &&
	    (i != instance->msix_vectors)) {
		if (instance->msix_vectors)
			pci_free_irq_vectors(instance->pdev);
		/* Disable Balanced IOPS mode and try realloc vectors */
		instance->perf_mode = MR_LATENCY_PERF_MODE;
		instance->low_latency_index_start = 1;
		num_msix_req = num_online_cpus() + instance->low_latency_index_start;

		instance->msix_vectors = min(num_msix_req,
				instance->msix_vectors);

		i = __megasas_alloc_irq_vectors(instance);

	}

	dev_info(&instance->pdev->dev,
		"requested/available msix %d/%d\n", instance->msix_vectors, i);

	if (i > 0)
		instance->msix_vectors = i;
	else
		instance->msix_vectors = 0;

	if (instance->smp_affinity_enable)
		megasas_set_high_iops_queue_affinity_hint(instance);
}