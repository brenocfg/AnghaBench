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
struct kfd_gpu_cache_info {scalar_t__ num_cu_shared; } ;
struct kfd_dev {TYPE_1__* device_info; } ;
struct kfd_cu_info {int num_shader_engines; int num_shader_arrays_per_engine; int num_cu_per_sh; int /*<<< orphan*/ ** cu_bitmap; } ;
struct crat_subtype_cache {int dummy; } ;
struct TYPE_2__ {int asic_family; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct kfd_gpu_cache_info*) ; 
#define  CHIP_ARCTURUS 142 
#define  CHIP_CARRIZO 141 
#define  CHIP_FIJI 140 
#define  CHIP_HAWAII 139 
#define  CHIP_KAVERI 138 
#define  CHIP_NAVI10 137 
#define  CHIP_POLARIS10 136 
#define  CHIP_POLARIS11 135 
#define  CHIP_POLARIS12 134 
#define  CHIP_RAVEN 133 
#define  CHIP_TONGA 132 
#define  CHIP_VEGA10 131 
#define  CHIP_VEGA12 130 
#define  CHIP_VEGA20 129 
#define  CHIP_VEGAM 128 
 int EINVAL ; 
 struct kfd_gpu_cache_info* carrizo_cache_info ; 
 struct kfd_gpu_cache_info* fiji_cache_info ; 
 int fill_in_pcache (struct crat_subtype_cache*,struct kfd_gpu_cache_info*,struct kfd_cu_info*,int,int /*<<< orphan*/ ,int,unsigned int,int) ; 
 struct kfd_gpu_cache_info* hawaii_cache_info ; 
 struct kfd_gpu_cache_info* kaveri_cache_info ; 
 struct kfd_gpu_cache_info* navi10_cache_info ; 
 struct kfd_gpu_cache_info* polaris10_cache_info ; 
 struct kfd_gpu_cache_info* polaris11_cache_info ; 
 struct kfd_gpu_cache_info* polaris12_cache_info ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 struct kfd_gpu_cache_info* raven_cache_info ; 
 struct kfd_gpu_cache_info* tonga_cache_info ; 
 struct kfd_gpu_cache_info* vega10_cache_info ; 
 struct kfd_gpu_cache_info* vegam_cache_info ; 

__attribute__((used)) static int kfd_fill_gpu_cache_info(struct kfd_dev *kdev,
			int gpu_processor_id,
			int available_size,
			struct kfd_cu_info *cu_info,
			struct crat_subtype_cache *pcache,
			int *size_filled,
			int *num_of_entries)
{
	struct kfd_gpu_cache_info *pcache_info;
	int num_of_cache_types = 0;
	int i, j, k;
	int ct = 0;
	int mem_available = available_size;
	unsigned int cu_processor_id;
	int ret;

	switch (kdev->device_info->asic_family) {
	case CHIP_KAVERI:
		pcache_info = kaveri_cache_info;
		num_of_cache_types = ARRAY_SIZE(kaveri_cache_info);
		break;
	case CHIP_HAWAII:
		pcache_info = hawaii_cache_info;
		num_of_cache_types = ARRAY_SIZE(hawaii_cache_info);
		break;
	case CHIP_CARRIZO:
		pcache_info = carrizo_cache_info;
		num_of_cache_types = ARRAY_SIZE(carrizo_cache_info);
		break;
	case CHIP_TONGA:
		pcache_info = tonga_cache_info;
		num_of_cache_types = ARRAY_SIZE(tonga_cache_info);
		break;
	case CHIP_FIJI:
		pcache_info = fiji_cache_info;
		num_of_cache_types = ARRAY_SIZE(fiji_cache_info);
		break;
	case CHIP_POLARIS10:
		pcache_info = polaris10_cache_info;
		num_of_cache_types = ARRAY_SIZE(polaris10_cache_info);
		break;
	case CHIP_POLARIS11:
		pcache_info = polaris11_cache_info;
		num_of_cache_types = ARRAY_SIZE(polaris11_cache_info);
		break;
	case CHIP_POLARIS12:
		pcache_info = polaris12_cache_info;
		num_of_cache_types = ARRAY_SIZE(polaris12_cache_info);
		break;
	case CHIP_VEGAM:
		pcache_info = vegam_cache_info;
		num_of_cache_types = ARRAY_SIZE(vegam_cache_info);
		break;
	case CHIP_VEGA10:
	case CHIP_VEGA12:
	case CHIP_VEGA20:
	case CHIP_ARCTURUS:
		pcache_info = vega10_cache_info;
		num_of_cache_types = ARRAY_SIZE(vega10_cache_info);
		break;
	case CHIP_RAVEN:
		pcache_info = raven_cache_info;
		num_of_cache_types = ARRAY_SIZE(raven_cache_info);
		break;
	case CHIP_NAVI10:
		pcache_info = navi10_cache_info;
		num_of_cache_types = ARRAY_SIZE(navi10_cache_info);
		break;
	default:
		return -EINVAL;
	}

	*size_filled = 0;
	*num_of_entries = 0;

	/* For each type of cache listed in the kfd_gpu_cache_info table,
	 * go through all available Compute Units.
	 * The [i,j,k] loop will
	 *		if kfd_gpu_cache_info.num_cu_shared = 1
	 *			will parse through all available CU
	 *		If (kfd_gpu_cache_info.num_cu_shared != 1)
	 *			then it will consider only one CU from
	 *			the shared unit
	 */

	for (ct = 0; ct < num_of_cache_types; ct++) {
		cu_processor_id = gpu_processor_id;
		for (i = 0; i < cu_info->num_shader_engines; i++) {
			for (j = 0; j < cu_info->num_shader_arrays_per_engine;
				j++) {
				for (k = 0; k < cu_info->num_cu_per_sh;
					k += pcache_info[ct].num_cu_shared) {

					ret = fill_in_pcache(pcache,
						pcache_info,
						cu_info,
						mem_available,
						cu_info->cu_bitmap[i][j],
						ct,
						cu_processor_id,
						k);

					if (ret < 0)
						break;

					if (!ret) {
						pcache++;
						(*num_of_entries)++;
						mem_available -=
							sizeof(*pcache);
						(*size_filled) +=
							sizeof(*pcache);
					}

					/* Move to next CU block */
					cu_processor_id +=
						pcache_info[ct].num_cu_shared;
				}
			}
		}
	}

	pr_debug("Added [%d] GPU cache entries\n", *num_of_entries);

	return 0;
}