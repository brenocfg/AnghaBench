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
struct dpages {unsigned int context_u; int /*<<< orphan*/  context_ptr; } ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void km_get_page(struct dpages *dp, struct page **p, unsigned long *len,
			unsigned *offset)
{
	*p = virt_to_page(dp->context_ptr);
	*offset = dp->context_u;
	*len = PAGE_SIZE - dp->context_u;
}