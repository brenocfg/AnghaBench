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
struct TYPE_2__ {int /*<<< orphan*/  tasklet; } ;
struct intel_engine_cs {TYPE_1__ execlists; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  execlists_submission_tasklet ; 
 int /*<<< orphan*/  intel_engine_setup_common (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  logical_ring_default_irqs (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  logical_ring_default_vfuncs (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void
logical_ring_setup(struct intel_engine_cs *engine)
{
	intel_engine_setup_common(engine);

	/* Intentionally left blank. */
	engine->buffer = NULL;

	tasklet_init(&engine->execlists.tasklet,
		     execlists_submission_tasklet, (unsigned long)engine);

	logical_ring_default_vfuncs(engine);
	logical_ring_default_irqs(engine);
}