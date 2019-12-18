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
struct journal_sector {int /*<<< orphan*/  mac; } ;
struct dm_integrity_c {int /*<<< orphan*/  journal_mac; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 unsigned int JOURNAL_BLOCK_SECTORS ; 
 unsigned int JOURNAL_MAC_PER_SECTOR ; 
 int JOURNAL_MAC_SIZE ; 
 struct journal_sector* access_journal (struct dm_integrity_c*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dm_integrity_io_error (struct dm_integrity_c*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  section_mac (struct dm_integrity_c*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rw_section_mac(struct dm_integrity_c *ic, unsigned section, bool wr)
{
	__u8 result[JOURNAL_MAC_SIZE];
	unsigned j;

	if (!ic->journal_mac)
		return;

	section_mac(ic, section, result);

	for (j = 0; j < JOURNAL_BLOCK_SECTORS; j++) {
		struct journal_sector *js = access_journal(ic, section, j);

		if (likely(wr))
			memcpy(&js->mac, result + (j * JOURNAL_MAC_PER_SECTOR), JOURNAL_MAC_PER_SECTOR);
		else {
			if (memcmp(&js->mac, result + (j * JOURNAL_MAC_PER_SECTOR), JOURNAL_MAC_PER_SECTOR))
				dm_integrity_io_error(ic, "journal mac", -EILSEQ);
		}
	}
}