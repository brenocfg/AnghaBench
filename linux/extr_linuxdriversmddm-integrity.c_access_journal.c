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
struct journal_sector {int dummy; } ;
struct dm_integrity_c {int /*<<< orphan*/  journal; } ;

/* Variables and functions */
 struct journal_sector* access_page_list (struct dm_integrity_c*,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct journal_sector *access_journal(struct dm_integrity_c *ic, unsigned section, unsigned offset)
{
	return access_page_list(ic, ic->journal, section, offset, NULL);
}