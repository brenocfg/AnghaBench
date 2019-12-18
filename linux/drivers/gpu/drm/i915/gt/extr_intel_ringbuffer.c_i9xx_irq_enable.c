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
struct intel_engine_cs {int /*<<< orphan*/  uncore; TYPE_1__* i915; int /*<<< orphan*/  irq_enable_mask; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN2_IMR ; 
 int /*<<< orphan*/  intel_uncore_posting_read_fw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
i9xx_irq_enable(struct intel_engine_cs *engine)
{
	engine->i915->irq_mask &= ~engine->irq_enable_mask;
	intel_uncore_write(engine->uncore, GEN2_IMR, engine->i915->irq_mask);
	intel_uncore_posting_read_fw(engine->uncore, GEN2_IMR);
}