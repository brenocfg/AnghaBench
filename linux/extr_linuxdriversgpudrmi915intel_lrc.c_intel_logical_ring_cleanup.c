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
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct TYPE_3__ {TYPE_2__ tasklet; } ;
struct intel_engine_cs {size_t id; struct drm_i915_private* i915; int /*<<< orphan*/  (* cleanup ) (struct intel_engine_cs*) ;scalar_t__ buffer; TYPE_1__ execlists; } ;
struct drm_i915_private {int /*<<< orphan*/ ** engine; } ;

/* Variables and functions */
 int I915_READ_MODE (struct intel_engine_cs*) ; 
 int MODE_IDLE ; 
 int /*<<< orphan*/  TASKLET_STATE_SCHED ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  intel_engine_cleanup_common (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  kfree (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  lrc_destroy_wa_ctx (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  stub1 (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  tasklet_kill (TYPE_2__*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void intel_logical_ring_cleanup(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv;

	/*
	 * Tasklet cannot be active at this point due intel_mark_active/idle
	 * so this is just for documentation.
	 */
	if (WARN_ON(test_bit(TASKLET_STATE_SCHED,
			     &engine->execlists.tasklet.state)))
		tasklet_kill(&engine->execlists.tasklet);

	dev_priv = engine->i915;

	if (engine->buffer) {
		WARN_ON((I915_READ_MODE(engine) & MODE_IDLE) == 0);
	}

	if (engine->cleanup)
		engine->cleanup(engine);

	intel_engine_cleanup_common(engine);

	lrc_destroy_wa_ctx(engine);

	engine->i915 = NULL;
	dev_priv->engine[engine->id] = NULL;
	kfree(engine);
}