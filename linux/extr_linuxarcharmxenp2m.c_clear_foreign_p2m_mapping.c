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
struct gnttab_unmap_grant_ref {int host_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_P2M_ENTRY ; 
 int XEN_PAGE_SHIFT ; 
 int /*<<< orphan*/  set_phys_to_machine (int,int /*<<< orphan*/ ) ; 

int clear_foreign_p2m_mapping(struct gnttab_unmap_grant_ref *unmap_ops,
			      struct gnttab_unmap_grant_ref *kunmap_ops,
			      struct page **pages, unsigned int count)
{
	int i;

	for (i = 0; i < count; i++) {
		set_phys_to_machine(unmap_ops[i].host_addr >> XEN_PAGE_SHIFT,
				    INVALID_P2M_ENTRY);
	}

	return 0;
}