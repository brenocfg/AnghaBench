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
typedef  int /*<<< orphan*/  grant_ref_t ;

/* Variables and functions */
 int /*<<< orphan*/  gnttab_add_deferred (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ gnttab_end_foreign_access_ref (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_free_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * virt_to_page (unsigned long) ; 

void gnttab_end_foreign_access(grant_ref_t ref, int readonly,
			       unsigned long page)
{
	if (gnttab_end_foreign_access_ref(ref, readonly)) {
		put_free_entry(ref);
		if (page != 0)
			put_page(virt_to_page(page));
	} else
		gnttab_add_deferred(ref, readonly,
				    page ? virt_to_page(page) : NULL);
}