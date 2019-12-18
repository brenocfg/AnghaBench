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
struct dm_integrity_c {unsigned int journal_section_sectors; } ;

/* Variables and functions */
 unsigned int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 unsigned int SECTOR_SHIFT ; 
 int /*<<< orphan*/  access_journal_check (struct dm_integrity_c*,unsigned int,unsigned int,int,char*) ; 

__attribute__((used)) static void page_list_location(struct dm_integrity_c *ic, unsigned section, unsigned offset,
			       unsigned *pl_index, unsigned *pl_offset)
{
	unsigned sector;

	access_journal_check(ic, section, offset, false, "page_list_location");

	sector = section * ic->journal_section_sectors + offset;

	*pl_index = sector >> (PAGE_SHIFT - SECTOR_SHIFT);
	*pl_offset = (sector << SECTOR_SHIFT) & (PAGE_SIZE - 1);
}