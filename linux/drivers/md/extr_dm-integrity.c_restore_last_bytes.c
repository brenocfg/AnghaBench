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
struct journal_sector {int /*<<< orphan*/  commit_id; } ;
struct journal_entry {int /*<<< orphan*/ * last_bytes; } ;
struct dm_integrity_c {unsigned int sectors_per_block; } ;

/* Variables and functions */

__attribute__((used)) static void restore_last_bytes(struct dm_integrity_c *ic, struct journal_sector *js,
			       struct journal_entry *je)
{
	unsigned s = 0;
	do {
		js->commit_id = je->last_bytes[s];
		js++;
	} while (++s < ic->sectors_per_block);
}