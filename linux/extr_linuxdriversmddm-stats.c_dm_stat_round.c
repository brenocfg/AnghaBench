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
struct dm_stat_shared {unsigned long long stamp; int /*<<< orphan*/ * in_flight; } ;
struct dm_stat_percpu {unsigned long long* io_ticks; unsigned long long io_ticks_total; unsigned int time_in_queue; } ;
struct dm_stat {int stat_flags; } ;

/* Variables and functions */
 size_t READ ; 
 int STAT_PRECISE_TIMESTAMPS ; 
 size_t WRITE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 unsigned long long jiffies ; 
 int /*<<< orphan*/  ktime_get () ; 
 unsigned long long ktime_to_ns (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static void dm_stat_round(struct dm_stat *s, struct dm_stat_shared *shared,
			  struct dm_stat_percpu *p)
{
	/*
	 * This is racy, but so is part_round_stats_single.
	 */
	unsigned long long now, difference;
	unsigned in_flight_read, in_flight_write;

	if (likely(!(s->stat_flags & STAT_PRECISE_TIMESTAMPS)))
		now = jiffies;
	else
		now = ktime_to_ns(ktime_get());

	difference = now - shared->stamp;
	if (!difference)
		return;

	in_flight_read = (unsigned)atomic_read(&shared->in_flight[READ]);
	in_flight_write = (unsigned)atomic_read(&shared->in_flight[WRITE]);
	if (in_flight_read)
		p->io_ticks[READ] += difference;
	if (in_flight_write)
		p->io_ticks[WRITE] += difference;
	if (in_flight_read + in_flight_write) {
		p->io_ticks_total += difference;
		p->time_in_queue += (in_flight_read + in_flight_write) * difference;
	}
	shared->stamp = now;
}