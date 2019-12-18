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
typedef  void* uint8_t ;
struct kfd_gpu_cache_info {int num_cu_shared; int /*<<< orphan*/  cache_size; int /*<<< orphan*/  cache_level; int /*<<< orphan*/  flags; } ;
struct kfd_cu_info {int dummy; } ;
struct crat_subtype_cache {int length; unsigned int processor_id_low; void** sibling_map; int /*<<< orphan*/  cache_size; int /*<<< orphan*/  cache_level; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRAT_SUBTYPE_CACHE_AFFINITY ; 
 int ENOMEM ; 
 int ffs (unsigned int) ; 
 int /*<<< orphan*/  memset (struct crat_subtype_cache*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fill_in_pcache(struct crat_subtype_cache *pcache,
				struct kfd_gpu_cache_info *pcache_info,
				struct kfd_cu_info *cu_info,
				int mem_available,
				int cu_bitmask,
				int cache_type, unsigned int cu_processor_id,
				int cu_block)
{
	unsigned int cu_sibling_map_mask;
	int first_active_cu;

	/* First check if enough memory is available */
	if (sizeof(struct crat_subtype_cache) > mem_available)
		return -ENOMEM;

	cu_sibling_map_mask = cu_bitmask;
	cu_sibling_map_mask >>= cu_block;
	cu_sibling_map_mask &=
		((1 << pcache_info[cache_type].num_cu_shared) - 1);
	first_active_cu = ffs(cu_sibling_map_mask);

	/* CU could be inactive. In case of shared cache find the first active
	 * CU. and incase of non-shared cache check if the CU is inactive. If
	 * inactive active skip it
	 */
	if (first_active_cu) {
		memset(pcache, 0, sizeof(struct crat_subtype_cache));
		pcache->type = CRAT_SUBTYPE_CACHE_AFFINITY;
		pcache->length = sizeof(struct crat_subtype_cache);
		pcache->flags = pcache_info[cache_type].flags;
		pcache->processor_id_low = cu_processor_id
					 + (first_active_cu - 1);
		pcache->cache_level = pcache_info[cache_type].cache_level;
		pcache->cache_size = pcache_info[cache_type].cache_size;

		/* Sibling map is w.r.t processor_id_low, so shift out
		 * inactive CU
		 */
		cu_sibling_map_mask =
			cu_sibling_map_mask >> (first_active_cu - 1);

		pcache->sibling_map[0] = (uint8_t)(cu_sibling_map_mask & 0xFF);
		pcache->sibling_map[1] =
				(uint8_t)((cu_sibling_map_mask >> 8) & 0xFF);
		pcache->sibling_map[2] =
				(uint8_t)((cu_sibling_map_mask >> 16) & 0xFF);
		pcache->sibling_map[3] =
				(uint8_t)((cu_sibling_map_mask >> 24) & 0xFF);
		return 0;
	}
	return 1;
}