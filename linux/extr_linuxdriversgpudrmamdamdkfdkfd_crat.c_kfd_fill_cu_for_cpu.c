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
struct crat_subtype_computeunit {int length; int proximity_domain; int processor_id_low; int /*<<< orphan*/  num_cpu_cores; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRAT_CU_FLAGS_CPU_PRESENT ; 
 int /*<<< orphan*/  CRAT_SUBTYPE_COMPUTEUNIT_AFFINITY ; 
 int /*<<< orphan*/  CRAT_SUBTYPE_FLAGS_ENABLED ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct cpumask* cpumask_of_node (int) ; 
 int /*<<< orphan*/  cpumask_weight (struct cpumask const*) ; 
 int kfd_numa_node_to_apic_id (int) ; 
 int /*<<< orphan*/  memset (struct crat_subtype_computeunit*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int kfd_fill_cu_for_cpu(int numa_node_id, int *avail_size,
				int proximity_domain,
				struct crat_subtype_computeunit *sub_type_hdr)
{
	const struct cpumask *cpumask;

	*avail_size -= sizeof(struct crat_subtype_computeunit);
	if (*avail_size < 0)
		return -ENOMEM;

	memset(sub_type_hdr, 0, sizeof(struct crat_subtype_computeunit));

	/* Fill in subtype header data */
	sub_type_hdr->type = CRAT_SUBTYPE_COMPUTEUNIT_AFFINITY;
	sub_type_hdr->length = sizeof(struct crat_subtype_computeunit);
	sub_type_hdr->flags = CRAT_SUBTYPE_FLAGS_ENABLED;

	cpumask = cpumask_of_node(numa_node_id);

	/* Fill in CU data */
	sub_type_hdr->flags |= CRAT_CU_FLAGS_CPU_PRESENT;
	sub_type_hdr->proximity_domain = proximity_domain;
	sub_type_hdr->processor_id_low = kfd_numa_node_to_apic_id(numa_node_id);
	if (sub_type_hdr->processor_id_low == -1)
		return -EINVAL;

	sub_type_hdr->num_cpu_cores = cpumask_weight(cpumask);

	return 0;
}