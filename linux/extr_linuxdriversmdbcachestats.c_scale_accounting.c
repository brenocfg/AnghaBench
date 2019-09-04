#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  expires; } ;
struct TYPE_5__ {unsigned int cache_hits; unsigned int cache_misses; unsigned int cache_bypass_hits; unsigned int cache_bypass_misses; unsigned int cache_readaheads; unsigned int cache_miss_collisions; unsigned int sectors_bypassed; } ;
struct TYPE_4__ {int /*<<< orphan*/  sectors_bypassed; int /*<<< orphan*/  cache_miss_collisions; int /*<<< orphan*/  cache_readaheads; int /*<<< orphan*/  cache_bypass_misses; int /*<<< orphan*/  cache_bypass_hits; int /*<<< orphan*/  cache_misses; int /*<<< orphan*/  cache_hits; } ;
struct cache_accounting {int /*<<< orphan*/  cl; TYPE_3__ timer; int /*<<< orphan*/  closing; TYPE_2__ five_minute; TYPE_2__ hour; TYPE_2__ day; TYPE_2__ total; TYPE_1__ collector; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAY_RESCALE ; 
 int /*<<< orphan*/  FIVE_MINUTE_RESCALE ; 
 int /*<<< orphan*/  HOUR_RESCALE ; 
 struct cache_accounting* acc ; 
 scalar_t__ accounting_delay ; 
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 unsigned int atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closure_return (int /*<<< orphan*/ *) ; 
 struct cache_accounting* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scale_stats (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void scale_accounting(struct timer_list *t)
{
	struct cache_accounting *acc = from_timer(acc, t, timer);

#define move_stat(name) do {						\
	unsigned int t = atomic_xchg(&acc->collector.name, 0);		\
	t <<= 16;							\
	acc->five_minute.name += t;					\
	acc->hour.name += t;						\
	acc->day.name += t;						\
	acc->total.name += t;						\
} while (0)

	move_stat(cache_hits);
	move_stat(cache_misses);
	move_stat(cache_bypass_hits);
	move_stat(cache_bypass_misses);
	move_stat(cache_readaheads);
	move_stat(cache_miss_collisions);
	move_stat(sectors_bypassed);

	scale_stats(&acc->total, 0);
	scale_stats(&acc->day, DAY_RESCALE);
	scale_stats(&acc->hour, HOUR_RESCALE);
	scale_stats(&acc->five_minute, FIVE_MINUTE_RESCALE);

	acc->timer.expires += accounting_delay;

	if (!atomic_read(&acc->closing))
		add_timer(&acc->timer);
	else
		closure_return(&acc->cl);
}