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
struct intel_engine_cs {TYPE_1__* gt; int /*<<< orphan*/  (* irq_disable ) (struct intel_engine_cs*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct intel_engine_cs*) ; 

__attribute__((used)) static void irq_disable(struct intel_engine_cs *engine)
{
	if (!engine->irq_disable)
		return;

	/* Caller disables interrupts */
	spin_lock(&engine->gt->irq_lock);
	engine->irq_disable(engine);
	spin_unlock(&engine->gt->irq_lock);
}