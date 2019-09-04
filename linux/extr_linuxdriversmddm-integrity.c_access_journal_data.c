#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct journal_sector {int dummy; } ;
struct dm_integrity_c {TYPE_1__* sb; } ;
struct TYPE_2__ {unsigned int log2_sectors_per_block; } ;

/* Variables and functions */
 scalar_t__ JOURNAL_BLOCK_SECTORS ; 
 struct journal_sector* access_journal (struct dm_integrity_c*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  access_journal_check (struct dm_integrity_c*,unsigned int,unsigned int,int,char*) ; 

__attribute__((used)) static struct journal_sector *access_journal_data(struct dm_integrity_c *ic, unsigned section, unsigned n)
{
	n <<= ic->sb->log2_sectors_per_block;

	n += JOURNAL_BLOCK_SECTORS;

	access_journal_check(ic, section, n, false, "access_journal_data");

	return access_journal(ic, section, n);
}