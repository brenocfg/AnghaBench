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
struct dm_integrity_c {unsigned int journal_section_entries; unsigned int journal_section_sectors; unsigned int journal_sections; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DMCRIT (char*,char const*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void access_journal_check(struct dm_integrity_c *ic, unsigned section, unsigned offset,
				 bool e, const char *function)
{
#if defined(CONFIG_DM_DEBUG) || defined(INTERNAL_VERIFY)
	unsigned limit = e ? ic->journal_section_entries : ic->journal_section_sectors;

	if (unlikely(section >= ic->journal_sections) ||
	    unlikely(offset >= limit)) {
		DMCRIT("%s: invalid access at (%u,%u), limit (%u,%u)",
		       function, section, offset, ic->journal_sections, limit);
		BUG();
	}
#endif
}