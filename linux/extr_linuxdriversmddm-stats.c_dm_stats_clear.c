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
struct dm_stats {int /*<<< orphan*/  mutex; } ;
struct dm_stat {int /*<<< orphan*/  n_entries; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  __dm_stat_clear (struct dm_stat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dm_stat* __dm_stats_find (struct dm_stats*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dm_stats_clear(struct dm_stats *stats, int id)
{
	struct dm_stat *s;

	mutex_lock(&stats->mutex);

	s = __dm_stats_find(stats, id);
	if (!s) {
		mutex_unlock(&stats->mutex);
		return -ENOENT;
	}

	__dm_stat_clear(s, 0, s->n_entries, true);

	mutex_unlock(&stats->mutex);

	return 1;
}