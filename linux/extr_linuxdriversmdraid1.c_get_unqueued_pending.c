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
struct r1conf {int /*<<< orphan*/ * nr_queued; int /*<<< orphan*/ * nr_pending; int /*<<< orphan*/  nr_sync_pending; } ;

/* Variables and functions */
 int BARRIER_BUCKETS_NR ; 
 int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_unqueued_pending(struct r1conf *conf)
{
	int idx, ret;

	ret = atomic_read(&conf->nr_sync_pending);
	for (idx = 0; idx < BARRIER_BUCKETS_NR; idx++)
		ret += atomic_read(&conf->nr_pending[idx]) -
			atomic_read(&conf->nr_queued[idx]);

	return ret;
}