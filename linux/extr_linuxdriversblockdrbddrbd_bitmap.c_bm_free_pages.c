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

/* Variables and functions */
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int /*<<< orphan*/  pr_alert (char*,unsigned long,unsigned long) ; 

__attribute__((used)) static void bm_free_pages(struct page **pages, unsigned long number)
{
	unsigned long i;
	if (!pages)
		return;

	for (i = 0; i < number; i++) {
		if (!pages[i]) {
			pr_alert("bm_free_pages tried to free a NULL pointer; i=%lu n=%lu\n",
				 i, number);
			continue;
		}
		__free_page(pages[i]);
		pages[i] = NULL;
	}
}