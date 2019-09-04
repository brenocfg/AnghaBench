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
struct page_key_data {struct page_key_data* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 struct page_key_data* page_key_data ; 

void page_key_free(void)
{
	struct page_key_data *pkd;

	while (page_key_data) {
		pkd = page_key_data;
		page_key_data = pkd->next;
		free_page((unsigned long) pkd);
	}
}