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
struct TYPE_2__ {int /*<<< orphan*/  capability; int /*<<< orphan*/  cpu_core_id_base; int /*<<< orphan*/  cpu_cores_count; } ;
struct kfd_topology_device {TYPE_1__ node_props; } ;
struct crat_subtype_computeunit {int hsa_capability; int /*<<< orphan*/  processor_id_low; int /*<<< orphan*/  num_cpu_cores; } ;

/* Variables and functions */
 int CRAT_CU_FLAGS_IOMMU_PRESENT ; 
 int /*<<< orphan*/  HSA_CAP_ATS_PRESENT ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kfd_populated_cu_info_cpu(struct kfd_topology_device *dev,
		struct crat_subtype_computeunit *cu)
{
	dev->node_props.cpu_cores_count = cu->num_cpu_cores;
	dev->node_props.cpu_core_id_base = cu->processor_id_low;
	if (cu->hsa_capability & CRAT_CU_FLAGS_IOMMU_PRESENT)
		dev->node_props.capability |= HSA_CAP_ATS_PRESENT;

	pr_debug("CU CPU: cores=%d id_base=%d\n", cu->num_cpu_cores,
			cu->processor_id_low);
}