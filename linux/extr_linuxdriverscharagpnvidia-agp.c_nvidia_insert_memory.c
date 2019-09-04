#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct agp_memory {int type; int page_count; int is_flushed; int /*<<< orphan*/ * pages; int /*<<< orphan*/  bridge; } ;
typedef  int off_t ;
struct TYPE_8__ {int num_active_entries; scalar_t__ pg_offset; } ;
struct TYPE_7__ {TYPE_1__* driver; scalar_t__ gatt_table; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* tlb_flush ) (struct agp_memory*) ;int /*<<< orphan*/  (* mask_memory ) (TYPE_2__*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PGE_EMPTY (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* agp_bridge ; 
 int agp_generic_type_to_mask_type (int /*<<< orphan*/ ,int) ; 
 int agp_memory_reserved ; 
 int /*<<< orphan*/  global_cache_flush () ; 
 TYPE_3__ nvidia_private ; 
 int /*<<< orphan*/  page_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct agp_memory*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int nvidia_insert_memory(struct agp_memory *mem, off_t pg_start, int type)
{
	int i, j;
	int mask_type;

	mask_type = agp_generic_type_to_mask_type(mem->bridge, type);
	if (mask_type != 0 || type != mem->type)
		return -EINVAL;

	if (mem->page_count == 0)
		return 0;

	if ((pg_start + mem->page_count) >
		(nvidia_private.num_active_entries - agp_memory_reserved/PAGE_SIZE))
		return -EINVAL;

	for (j = pg_start; j < (pg_start + mem->page_count); j++) {
		if (!PGE_EMPTY(agp_bridge, readl(agp_bridge->gatt_table+nvidia_private.pg_offset+j)))
			return -EBUSY;
	}

	if (!mem->is_flushed) {
		global_cache_flush();
		mem->is_flushed = true;
	}
	for (i = 0, j = pg_start; i < mem->page_count; i++, j++) {
		writel(agp_bridge->driver->mask_memory(agp_bridge,
			       page_to_phys(mem->pages[i]), mask_type),
			agp_bridge->gatt_table+nvidia_private.pg_offset+j);
	}

	/* PCI Posting. */
	readl(agp_bridge->gatt_table+nvidia_private.pg_offset+j - 1);

	agp_bridge->driver->tlb_flush(mem);
	return 0;
}