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
struct page {struct page* freelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ page_address (struct page*) ; 

__attribute__((used)) static void free_page_list(struct page *freelist)
{
	while (freelist != NULL) {
		unsigned long p = (unsigned long)page_address(freelist);
		freelist = freelist->freelist;
		free_page(p);
	}
}