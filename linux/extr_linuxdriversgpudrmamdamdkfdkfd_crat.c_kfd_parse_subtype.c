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
struct list_head {int dummy; } ;
struct crat_subtype_memory {int dummy; } ;
struct crat_subtype_iolink {int dummy; } ;
struct crat_subtype_generic {int type; } ;
struct crat_subtype_computeunit {int dummy; } ;
struct crat_subtype_cache {int dummy; } ;

/* Variables and functions */
#define  CRAT_SUBTYPE_CACHE_AFFINITY 133 
#define  CRAT_SUBTYPE_CCOMPUTE_AFFINITY 132 
#define  CRAT_SUBTYPE_COMPUTEUNIT_AFFINITY 131 
#define  CRAT_SUBTYPE_IOLINK_AFFINITY 130 
#define  CRAT_SUBTYPE_MEMORY_AFFINITY 129 
#define  CRAT_SUBTYPE_TLB_AFFINITY 128 
 int kfd_parse_subtype_cache (struct crat_subtype_cache*,struct list_head*) ; 
 int kfd_parse_subtype_cu (struct crat_subtype_computeunit*,struct list_head*) ; 
 int kfd_parse_subtype_iolink (struct crat_subtype_iolink*,struct list_head*) ; 
 int kfd_parse_subtype_mem (struct crat_subtype_memory*,struct list_head*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static int kfd_parse_subtype(struct crat_subtype_generic *sub_type_hdr,
				struct list_head *device_list)
{
	struct crat_subtype_computeunit *cu;
	struct crat_subtype_memory *mem;
	struct crat_subtype_cache *cache;
	struct crat_subtype_iolink *iolink;
	int ret = 0;

	switch (sub_type_hdr->type) {
	case CRAT_SUBTYPE_COMPUTEUNIT_AFFINITY:
		cu = (struct crat_subtype_computeunit *)sub_type_hdr;
		ret = kfd_parse_subtype_cu(cu, device_list);
		break;
	case CRAT_SUBTYPE_MEMORY_AFFINITY:
		mem = (struct crat_subtype_memory *)sub_type_hdr;
		ret = kfd_parse_subtype_mem(mem, device_list);
		break;
	case CRAT_SUBTYPE_CACHE_AFFINITY:
		cache = (struct crat_subtype_cache *)sub_type_hdr;
		ret = kfd_parse_subtype_cache(cache, device_list);
		break;
	case CRAT_SUBTYPE_TLB_AFFINITY:
		/*
		 * For now, nothing to do here
		 */
		pr_debug("Found TLB entry in CRAT table (not processing)\n");
		break;
	case CRAT_SUBTYPE_CCOMPUTE_AFFINITY:
		/*
		 * For now, nothing to do here
		 */
		pr_debug("Found CCOMPUTE entry in CRAT table (not processing)\n");
		break;
	case CRAT_SUBTYPE_IOLINK_AFFINITY:
		iolink = (struct crat_subtype_iolink *)sub_type_hdr;
		ret = kfd_parse_subtype_iolink(iolink, device_list);
		break;
	default:
		pr_warn("Unknown subtype %d in CRAT\n",
				sub_type_hdr->type);
	}

	return ret;
}