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
struct intel_engine_cs {TYPE_1__ timeline; } ;

/* Variables and functions */
 int __guc_dequeue (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  guc_submit (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void guc_dequeue(struct intel_engine_cs *engine)
{
	unsigned long flags;
	bool submit;

	local_irq_save(flags);

	spin_lock(&engine->timeline.lock);
	submit = __guc_dequeue(engine);
	spin_unlock(&engine->timeline.lock);

	if (submit)
		guc_submit(engine);

	local_irq_restore(flags);
}