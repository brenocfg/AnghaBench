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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct intel_engine_cs {TYPE_1__ stats; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  __intel_engine_get_busy_time (struct intel_engine_cs*) ; 
 unsigned int read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned int) ; 

ktime_t intel_engine_get_busy_time(struct intel_engine_cs *engine)
{
	unsigned int seq;
	ktime_t total;

	do {
		seq = read_seqbegin(&engine->stats.lock);
		total = __intel_engine_get_busy_time(engine);
	} while (read_seqretry(&engine->stats.lock, seq));

	return total;
}