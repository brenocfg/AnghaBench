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
struct TYPE_2__ {int capability; } ;
struct kfd_topology_device {int /*<<< orphan*/  perf_props; TYPE_1__ node_props; } ;
struct kfd_perf_properties {int max_concurrent; int /*<<< orphan*/  list; int /*<<< orphan*/  block_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int HSA_CAP_ATS_PRESENT ; 
 int amd_iommu_pc_get_max_banks (int /*<<< orphan*/ ) ; 
 int amd_iommu_pc_get_max_counters (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd_iommu_pc_supported () ; 
 struct kfd_perf_properties* kfd_alloc_struct (struct kfd_perf_properties*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int kfd_iommu_add_perf_counters(struct kfd_topology_device *kdev)
{
	struct kfd_perf_properties *props;

	if (!(kdev->node_props.capability & HSA_CAP_ATS_PRESENT))
		return 0;

	if (!amd_iommu_pc_supported())
		return 0;

	props = kfd_alloc_struct(props);
	if (!props)
		return -ENOMEM;
	strcpy(props->block_name, "iommu");
	props->max_concurrent = amd_iommu_pc_get_max_banks(0) *
		amd_iommu_pc_get_max_counters(0); /* assume one iommu */
	list_add_tail(&props->list, &kdev->perf_props);

	return 0;
}