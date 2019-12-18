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
struct gnttab_unmap_grant_ref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageForeign (struct page*) ; 
 int /*<<< orphan*/  GNTTABOP_unmap_grant_ref ; 
 int HYPERVISOR_grant_table_op (int /*<<< orphan*/ ,struct gnttab_unmap_grant_ref*,unsigned int) ; 
 int clear_foreign_p2m_mapping (struct gnttab_unmap_grant_ref*,struct gnttab_unmap_grant_ref*,struct page**,unsigned int) ; 

int gnttab_unmap_refs(struct gnttab_unmap_grant_ref *unmap_ops,
		      struct gnttab_unmap_grant_ref *kunmap_ops,
		      struct page **pages, unsigned int count)
{
	unsigned int i;
	int ret;

	ret = HYPERVISOR_grant_table_op(GNTTABOP_unmap_grant_ref, unmap_ops, count);
	if (ret)
		return ret;

	for (i = 0; i < count; i++)
		ClearPageForeign(pages[i]);

	return clear_foreign_p2m_mapping(unmap_ops, kunmap_ops, pages, count);
}