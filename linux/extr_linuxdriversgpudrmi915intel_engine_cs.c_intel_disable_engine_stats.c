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
struct TYPE_2__ {scalar_t__ enabled; int /*<<< orphan*/  lock; scalar_t__ active; int /*<<< orphan*/  total; } ;
struct intel_engine_cs {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __intel_engine_get_busy_time (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_supports_stats (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  write_seqlock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_sequnlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void intel_disable_engine_stats(struct intel_engine_cs *engine)
{
	unsigned long flags;

	if (!intel_engine_supports_stats(engine))
		return;

	write_seqlock_irqsave(&engine->stats.lock, flags);
	WARN_ON_ONCE(engine->stats.enabled == 0);
	if (--engine->stats.enabled == 0) {
		engine->stats.total = __intel_engine_get_busy_time(engine);
		engine->stats.active = 0;
	}
	write_sequnlock_irqrestore(&engine->stats.lock, flags);
}