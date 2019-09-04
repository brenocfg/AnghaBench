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
struct TYPE_2__ {int /*<<< orphan*/  capability; int /*<<< orphan*/  max_slots_scratch_cu; int /*<<< orphan*/  simd_per_cu; int /*<<< orphan*/  cu_per_simd_array; int /*<<< orphan*/  array_count; int /*<<< orphan*/  wave_front_size; int /*<<< orphan*/  max_waves_per_simd; int /*<<< orphan*/  lds_size_in_kb; int /*<<< orphan*/  simd_count; int /*<<< orphan*/  simd_id_base; } ;
struct kfd_topology_device {TYPE_1__ node_props; } ;
struct crat_subtype_computeunit {int hsa_capability; int /*<<< orphan*/  processor_id_low; int /*<<< orphan*/  max_slots_scatch_cu; int /*<<< orphan*/  num_simd_per_cu; int /*<<< orphan*/  num_cu_per_array; int /*<<< orphan*/  array_count; int /*<<< orphan*/  wave_front_size; int /*<<< orphan*/  max_waves_simd; int /*<<< orphan*/  lds_size_in_kb; int /*<<< orphan*/  num_simd_cores; } ;

/* Variables and functions */
 int CRAT_CU_FLAGS_HOT_PLUGGABLE ; 
 int /*<<< orphan*/  HSA_CAP_HOT_PLUGGABLE ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kfd_populated_cu_info_gpu(struct kfd_topology_device *dev,
		struct crat_subtype_computeunit *cu)
{
	dev->node_props.simd_id_base = cu->processor_id_low;
	dev->node_props.simd_count = cu->num_simd_cores;
	dev->node_props.lds_size_in_kb = cu->lds_size_in_kb;
	dev->node_props.max_waves_per_simd = cu->max_waves_simd;
	dev->node_props.wave_front_size = cu->wave_front_size;
	dev->node_props.array_count = cu->array_count;
	dev->node_props.cu_per_simd_array = cu->num_cu_per_array;
	dev->node_props.simd_per_cu = cu->num_simd_per_cu;
	dev->node_props.max_slots_scratch_cu = cu->max_slots_scatch_cu;
	if (cu->hsa_capability & CRAT_CU_FLAGS_HOT_PLUGGABLE)
		dev->node_props.capability |= HSA_CAP_HOT_PLUGGABLE;
	pr_debug("CU GPU: id_base=%d\n", cu->processor_id_low);
}