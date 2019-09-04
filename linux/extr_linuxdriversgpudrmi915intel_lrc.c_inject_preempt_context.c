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
struct intel_engine_execlists {scalar_t__ preempt_complete_status; scalar_t__ ctrl_reg; } ;
struct intel_engine_cs {int /*<<< orphan*/  name; TYPE_1__* i915; struct intel_engine_execlists execlists; } ;
struct intel_context {int* lrc_reg_state; int /*<<< orphan*/  lrc_desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  preempt_context; } ;

/* Variables and functions */
 int CTX_CONTEXT_CONTROL ; 
 int CTX_CTRL_ENGINE_CTX_RESTORE_INHIBIT ; 
 int CTX_CTRL_ENGINE_CTX_SAVE_INHIBIT ; 
 int /*<<< orphan*/  EL_CTRL_LOAD ; 
 int /*<<< orphan*/  EXECLISTS_ACTIVE_HWACK ; 
 int /*<<< orphan*/  EXECLISTS_ACTIVE_PREEMPT ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ) ; 
 int _MASKED_BIT_ENABLE (int) ; 
 int /*<<< orphan*/  execlists_clear_active (struct intel_engine_execlists*,int /*<<< orphan*/ ) ; 
 unsigned int execlists_num_ports (struct intel_engine_execlists*) ; 
 int /*<<< orphan*/  execlists_set_active (struct intel_engine_execlists*,int /*<<< orphan*/ ) ; 
 struct intel_context* to_intel_context (int /*<<< orphan*/ ,struct intel_engine_cs*) ; 
 scalar_t__ upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_desc (struct intel_engine_execlists*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void inject_preempt_context(struct intel_engine_cs *engine)
{
	struct intel_engine_execlists *execlists = &engine->execlists;
	struct intel_context *ce =
		to_intel_context(engine->i915->preempt_context, engine);
	unsigned int n;

	GEM_BUG_ON(execlists->preempt_complete_status !=
		   upper_32_bits(ce->lrc_desc));
	GEM_BUG_ON((ce->lrc_reg_state[CTX_CONTEXT_CONTROL + 1] &
		    _MASKED_BIT_ENABLE(CTX_CTRL_ENGINE_CTX_RESTORE_INHIBIT |
				       CTX_CTRL_ENGINE_CTX_SAVE_INHIBIT)) !=
		   _MASKED_BIT_ENABLE(CTX_CTRL_ENGINE_CTX_RESTORE_INHIBIT |
				      CTX_CTRL_ENGINE_CTX_SAVE_INHIBIT));

	/*
	 * Switch to our empty preempt context so
	 * the state of the GPU is known (idle).
	 */
	GEM_TRACE("%s\n", engine->name);
	for (n = execlists_num_ports(execlists); --n; )
		write_desc(execlists, 0, n);

	write_desc(execlists, ce->lrc_desc, n);

	/* we need to manually load the submit queue */
	if (execlists->ctrl_reg)
		writel(EL_CTRL_LOAD, execlists->ctrl_reg);

	execlists_clear_active(execlists, EXECLISTS_ACTIVE_HWACK);
	execlists_set_active(execlists, EXECLISTS_ACTIVE_PREEMPT);
}