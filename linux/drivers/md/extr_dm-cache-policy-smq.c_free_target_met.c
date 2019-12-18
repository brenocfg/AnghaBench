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
struct TYPE_2__ {unsigned int nr_allocated; } ;
struct smq_policy {int /*<<< orphan*/  bg_work; TYPE_1__ cache_alloc; int /*<<< orphan*/  cache_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_TARGET ; 
 scalar_t__ btracker_nr_demotions_queued (int /*<<< orphan*/ ) ; 
 unsigned int from_cblock (int /*<<< orphan*/ ) ; 
 scalar_t__ percent_to_target (struct smq_policy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool free_target_met(struct smq_policy *mq)
{
	unsigned nr_free;

	nr_free = from_cblock(mq->cache_size) - mq->cache_alloc.nr_allocated;
	return (nr_free + btracker_nr_demotions_queued(mq->bg_work)) >=
		percent_to_target(mq, FREE_TARGET);
}