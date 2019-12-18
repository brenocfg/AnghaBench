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
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int /*<<< orphan*/  kvfree (struct page**) ; 

__attribute__((used)) static void imgu_dmamap_free_buffer(struct page **pages,
				    size_t size)
{
	int count = size >> PAGE_SHIFT;

	while (count--)
		__free_page(pages[count]);
	kvfree(pages);
}