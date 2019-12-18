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
struct journal_sector {int /*<<< orphan*/  commit_id; int /*<<< orphan*/  entries; } ;
struct journal_entry {int dummy; } ;
struct dm_integrity_c {unsigned int journal_section_sectors; unsigned int journal_section_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  JOURNAL_SECTOR_DATA ; 
 struct journal_sector* access_journal (struct dm_integrity_c*,unsigned int,unsigned int) ; 
 struct journal_entry* access_journal_entry (struct dm_integrity_c*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dm_integrity_commit_id (struct dm_integrity_c*,unsigned int,unsigned int,unsigned char) ; 
 int /*<<< orphan*/  journal_entry_set_unused (struct journal_entry*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wraparound_section (struct dm_integrity_c*,unsigned int*) ; 
 int /*<<< orphan*/  write_journal (struct dm_integrity_c*,unsigned int,unsigned int) ; 

__attribute__((used)) static void init_journal(struct dm_integrity_c *ic, unsigned start_section,
			 unsigned n_sections, unsigned char commit_seq)
{
	unsigned i, j, n;

	if (!n_sections)
		return;

	for (n = 0; n < n_sections; n++) {
		i = start_section + n;
		wraparound_section(ic, &i);
		for (j = 0; j < ic->journal_section_sectors; j++) {
			struct journal_sector *js = access_journal(ic, i, j);
			memset(&js->entries, 0, JOURNAL_SECTOR_DATA);
			js->commit_id = dm_integrity_commit_id(ic, i, j, commit_seq);
		}
		for (j = 0; j < ic->journal_section_entries; j++) {
			struct journal_entry *je = access_journal_entry(ic, i, j);
			journal_entry_set_unused(je);
		}
	}

	write_journal(ic, start_section, n_sections);
}