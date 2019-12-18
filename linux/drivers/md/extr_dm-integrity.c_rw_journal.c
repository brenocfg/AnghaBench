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
struct journal_completion {int dummy; } ;
struct dm_integrity_c {unsigned int journal_section_sectors; } ;

/* Variables and functions */
 int /*<<< orphan*/  rw_journal_sectors (struct dm_integrity_c*,int,int,unsigned int,unsigned int,struct journal_completion*) ; 

__attribute__((used)) static void rw_journal(struct dm_integrity_c *ic, int op, int op_flags, unsigned section,
		       unsigned n_sections, struct journal_completion *comp)
{
	unsigned sector, n_sectors;

	sector = section * ic->journal_section_sectors;
	n_sectors = n_sections * ic->journal_section_sectors;

	rw_journal_sectors(ic, op, op_flags, sector, n_sectors, comp);
}