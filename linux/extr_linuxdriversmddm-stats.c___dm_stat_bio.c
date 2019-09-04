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
struct dm_stats_aux {int dummy; } ;
struct dm_stat {scalar_t__ start; scalar_t__ end; scalar_t__ step; size_t n_entries; int /*<<< orphan*/  id; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMCRIT (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ dm_sector_div64 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dm_stat_for_entry (struct dm_stat*,size_t,int,scalar_t__,struct dm_stats_aux*,int,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void __dm_stat_bio(struct dm_stat *s, int bi_rw,
			  sector_t bi_sector, sector_t end_sector,
			  bool end, unsigned long duration_jiffies,
			  struct dm_stats_aux *stats_aux)
{
	sector_t rel_sector, offset, todo, fragment_len;
	size_t entry;

	if (end_sector <= s->start || bi_sector >= s->end)
		return;
	if (unlikely(bi_sector < s->start)) {
		rel_sector = 0;
		todo = end_sector - s->start;
	} else {
		rel_sector = bi_sector - s->start;
		todo = end_sector - bi_sector;
	}
	if (unlikely(end_sector > s->end))
		todo -= (end_sector - s->end);

	offset = dm_sector_div64(rel_sector, s->step);
	entry = rel_sector;
	do {
		if (WARN_ON_ONCE(entry >= s->n_entries)) {
			DMCRIT("Invalid area access in region id %d", s->id);
			return;
		}
		fragment_len = todo;
		if (fragment_len > s->step - offset)
			fragment_len = s->step - offset;
		dm_stat_for_entry(s, entry, bi_rw, fragment_len,
				  stats_aux, end, duration_jiffies);
		todo -= fragment_len;
		entry++;
		offset = 0;
	} while (unlikely(todo != 0));
}