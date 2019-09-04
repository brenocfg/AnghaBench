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
struct page {int dummy; } ;
struct gnttab_map_grant_ref {int host_addr; int dev_bus_addr; scalar_t__ status; } ;

/* Variables and functions */
 int XEN_PAGE_SHIFT ; 
 int /*<<< orphan*/  set_phys_to_machine (int,int) ; 

int set_foreign_p2m_mapping(struct gnttab_map_grant_ref *map_ops,
			    struct gnttab_map_grant_ref *kmap_ops,
			    struct page **pages, unsigned int count)
{
	int i;

	for (i = 0; i < count; i++) {
		if (map_ops[i].status)
			continue;
		set_phys_to_machine(map_ops[i].host_addr >> XEN_PAGE_SHIFT,
				    map_ops[i].dev_bus_addr >> XEN_PAGE_SHIFT);
	}

	return 0;
}