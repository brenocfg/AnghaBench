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
struct capsule_info {size_t index; int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 size_t NO_FURTHER_WRITE_ACTION ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void efi_free_all_buff_pages(struct capsule_info *cap_info)
{
	while (cap_info->index > 0)
		__free_page(cap_info->pages[--cap_info->index]);

	cap_info->index = NO_FURTHER_WRITE_ACTION;
}