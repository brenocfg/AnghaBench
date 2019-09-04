#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int num_of_pages; int last_page_available_bytes; } ;
struct TYPE_3__ {scalar_t__ first_page_offset; } ;
struct cio2_fbpt_entry {int lop_page_addr; TYPE_2__ second_entry; TYPE_1__ first_entry; } ;
struct cio2_device {int dummy_lop_bus_addr; } ;

/* Variables and functions */
 int CIO2_MAX_LOPS ; 
 int CIO2_PAGE_SIZE ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  cio2_fbpt_entry_enable (struct cio2_device*,struct cio2_fbpt_entry*) ; 

__attribute__((used)) static void cio2_fbpt_entry_init_dummy(struct cio2_device *cio2,
				       struct cio2_fbpt_entry
				       entry[CIO2_MAX_LOPS])
{
	unsigned int i;

	entry[0].first_entry.first_page_offset = 0;
	entry[1].second_entry.num_of_pages =
		CIO2_PAGE_SIZE / sizeof(u32) * CIO2_MAX_LOPS;
	entry[1].second_entry.last_page_available_bytes = CIO2_PAGE_SIZE - 1;

	for (i = 0; i < CIO2_MAX_LOPS; i++)
		entry[i].lop_page_addr = cio2->dummy_lop_bus_addr >> PAGE_SHIFT;

	cio2_fbpt_entry_enable(cio2, entry);
}