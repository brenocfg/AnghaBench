#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_breadcrumbs {int /*<<< orphan*/  hangcheck; int /*<<< orphan*/  fake_irq; } ;
struct intel_engine_cs {TYPE_2__* i915; int /*<<< orphan*/  id; struct intel_breadcrumbs breadcrumbs; } ;
struct TYPE_3__ {int /*<<< orphan*/  missed_irq_rings; } ;
struct TYPE_4__ {TYPE_1__ gpu_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cancel_fake_irq(struct intel_engine_cs *engine)
{
	struct intel_breadcrumbs *b = &engine->breadcrumbs;

	del_timer_sync(&b->fake_irq); /* may queue b->hangcheck */
	del_timer_sync(&b->hangcheck);
	clear_bit(engine->id, &engine->i915->gpu_error.missed_irq_rings);
}