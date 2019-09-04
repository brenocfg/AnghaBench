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
typedef  int u64 ;
struct blk_stat_callback {TYPE_1__* stat; } ;
struct TYPE_2__ {int mean; int /*<<< orphan*/  nr_samples; } ;

/* Variables and functions */
 int AWFUL ; 
 int BAD ; 
 int GOOD ; 
 int GREAT ; 
 int NONE ; 

__attribute__((used)) static int kyber_lat_status(struct blk_stat_callback *cb,
			    unsigned int sched_domain, u64 target)
{
	u64 latency;

	if (!cb->stat[sched_domain].nr_samples)
		return NONE;

	latency = cb->stat[sched_domain].mean;
	if (latency >= 2 * target)
		return AWFUL;
	else if (latency > target)
		return BAD;
	else if (latency <= target / 2)
		return GREAT;
	else /* (latency <= target) */
		return GOOD;
}