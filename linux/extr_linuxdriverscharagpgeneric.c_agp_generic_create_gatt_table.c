#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char u32 ;
struct page {int dummy; } ;
struct aper_size_info_fixed {int size; int page_order; int num_entries; } ;
struct agp_bridge_data {int aperture_size_idx; char* gatt_table_real; int /*<<< orphan*/ * gatt_table; int /*<<< orphan*/  scratch_page; int /*<<< orphan*/  gatt_bus_addr; TYPE_1__* driver; void* current_size; } ;
struct TYPE_8__ {int size; int page_order; int num_entries; } ;
struct TYPE_7__ {int size; int page_order; int num_entries; } ;
struct TYPE_6__ {int size; int page_order; int num_entries; } ;
struct TYPE_5__ {int size_type; int num_aperture_sizes; int /*<<< orphan*/  (* cache_flush ) () ;} ;

/* Variables and functions */
 void* A_IDX16 (struct agp_bridge_data*) ; 
 void* A_IDX32 (struct agp_bridge_data*) ; 
 void* A_IDX8 (struct agp_bridge_data*) ; 
 TYPE_4__* A_SIZE_16 (void*) ; 
 TYPE_3__* A_SIZE_32 (void*) ; 
 TYPE_2__* A_SIZE_8 (void*) ; 
 int /*<<< orphan*/  ClearPageReserved (struct page*) ; 
 int EINVAL ; 
 int ENOMEM ; 
#define  FIXED_APER_SIZE 132 
#define  LVL2_APER_SIZE 131 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageReserved (struct page*) ; 
#define  U16_APER_SIZE 130 
#define  U32_APER_SIZE 129 
#define  U8_APER_SIZE 128 
 void* agp_gatt_table ; 
 char* alloc_gatt_pages (int) ; 
 int /*<<< orphan*/  free_gatt_pages (char*,int) ; 
 int /*<<< orphan*/ * ioremap_nocache (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 struct page* virt_to_page (char*) ; 
 int /*<<< orphan*/  virt_to_phys (char*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int agp_generic_create_gatt_table(struct agp_bridge_data *bridge)
{
	char *table;
	char *table_end;
	int size;
	int page_order;
	int num_entries;
	int i;
	void *temp;
	struct page *page;

	/* The generic routines can't handle 2 level gatt's */
	if (bridge->driver->size_type == LVL2_APER_SIZE)
		return -EINVAL;

	table = NULL;
	i = bridge->aperture_size_idx;
	temp = bridge->current_size;
	size = page_order = num_entries = 0;

	if (bridge->driver->size_type != FIXED_APER_SIZE) {
		do {
			switch (bridge->driver->size_type) {
			case U8_APER_SIZE:
				size = A_SIZE_8(temp)->size;
				page_order =
				    A_SIZE_8(temp)->page_order;
				num_entries =
				    A_SIZE_8(temp)->num_entries;
				break;
			case U16_APER_SIZE:
				size = A_SIZE_16(temp)->size;
				page_order = A_SIZE_16(temp)->page_order;
				num_entries = A_SIZE_16(temp)->num_entries;
				break;
			case U32_APER_SIZE:
				size = A_SIZE_32(temp)->size;
				page_order = A_SIZE_32(temp)->page_order;
				num_entries = A_SIZE_32(temp)->num_entries;
				break;
				/* This case will never really happen. */
			case FIXED_APER_SIZE:
			case LVL2_APER_SIZE:
			default:
				size = page_order = num_entries = 0;
				break;
			}

			table = alloc_gatt_pages(page_order);

			if (table == NULL) {
				i++;
				switch (bridge->driver->size_type) {
				case U8_APER_SIZE:
					bridge->current_size = A_IDX8(bridge);
					break;
				case U16_APER_SIZE:
					bridge->current_size = A_IDX16(bridge);
					break;
				case U32_APER_SIZE:
					bridge->current_size = A_IDX32(bridge);
					break;
				/* These cases will never really happen. */
				case FIXED_APER_SIZE:
				case LVL2_APER_SIZE:
				default:
					break;
				}
				temp = bridge->current_size;
			} else {
				bridge->aperture_size_idx = i;
			}
		} while (!table && (i < bridge->driver->num_aperture_sizes));
	} else {
		size = ((struct aper_size_info_fixed *) temp)->size;
		page_order = ((struct aper_size_info_fixed *) temp)->page_order;
		num_entries = ((struct aper_size_info_fixed *) temp)->num_entries;
		table = alloc_gatt_pages(page_order);
	}

	if (table == NULL)
		return -ENOMEM;

	table_end = table + ((PAGE_SIZE * (1 << page_order)) - 1);

	for (page = virt_to_page(table); page <= virt_to_page(table_end); page++)
		SetPageReserved(page);

	bridge->gatt_table_real = (u32 *) table;
	agp_gatt_table = (void *)table;

	bridge->driver->cache_flush();
#ifdef CONFIG_X86
	if (set_memory_uc((unsigned long)table, 1 << page_order))
		printk(KERN_WARNING "Could not set GATT table memory to UC!\n");

	bridge->gatt_table = (u32 __iomem *)table;
#else
	bridge->gatt_table = ioremap_nocache(virt_to_phys(table),
					(PAGE_SIZE * (1 << page_order)));
	bridge->driver->cache_flush();
#endif

	if (bridge->gatt_table == NULL) {
		for (page = virt_to_page(table); page <= virt_to_page(table_end); page++)
			ClearPageReserved(page);

		free_gatt_pages(table, page_order);

		return -ENOMEM;
	}
	bridge->gatt_bus_addr = virt_to_phys(bridge->gatt_table_real);

	/* AK: bogus, should encode addresses > 4GB */
	for (i = 0; i < num_entries; i++) {
		writel(bridge->scratch_page, bridge->gatt_table+i);
		readl(bridge->gatt_table+i);	/* PCI Posting. */
	}

	return 0;
}