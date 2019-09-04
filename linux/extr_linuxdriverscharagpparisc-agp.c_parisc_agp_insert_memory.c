#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct agp_memory {int type; int page_count; int is_flushed; int /*<<< orphan*/ * pages; } ;
struct _parisc_agp_info {int io_pages_per_kpage; int gatt_entries; scalar_t__* gatt; scalar_t__ io_page_size; } ;
typedef  int off_t ;
struct TYPE_6__ {TYPE_1__* driver; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* tlb_flush ) (struct agp_memory*) ;scalar_t__ (* agp_type_to_mask_type ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 TYPE_2__* agp_bridge ; 
 int /*<<< orphan*/  global_cache_flush () ; 
 unsigned long page_to_phys (int /*<<< orphan*/ ) ; 
 struct _parisc_agp_info parisc_agp_info ; 
 scalar_t__ parisc_agp_mask_memory (TYPE_2__*,unsigned long,int) ; 
 scalar_t__ stub1 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub2 (struct agp_memory*) ; 

__attribute__((used)) static int
parisc_agp_insert_memory(struct agp_memory *mem, off_t pg_start, int type)
{
	struct _parisc_agp_info *info = &parisc_agp_info;
	int i, k;
	off_t j, io_pg_start;
	int io_pg_count;

	if (type != mem->type ||
		agp_bridge->driver->agp_type_to_mask_type(agp_bridge, type)) {
		return -EINVAL;
	}

	io_pg_start = info->io_pages_per_kpage * pg_start;
	io_pg_count = info->io_pages_per_kpage * mem->page_count;
	if ((io_pg_start + io_pg_count) > info->gatt_entries) {
		return -EINVAL;
	}

	j = io_pg_start;
	while (j < (io_pg_start + io_pg_count)) {
		if (info->gatt[j])
			return -EBUSY;
		j++;
	}

	if (!mem->is_flushed) {
		global_cache_flush();
		mem->is_flushed = true;
	}

	for (i = 0, j = io_pg_start; i < mem->page_count; i++) {
		unsigned long paddr;

		paddr = page_to_phys(mem->pages[i]);
		for (k = 0;
		     k < info->io_pages_per_kpage;
		     k++, j++, paddr += info->io_page_size) {
			info->gatt[j] =
				parisc_agp_mask_memory(agp_bridge,
					paddr, type);
		}
	}

	agp_bridge->driver->tlb_flush(mem);

	return 0;
}