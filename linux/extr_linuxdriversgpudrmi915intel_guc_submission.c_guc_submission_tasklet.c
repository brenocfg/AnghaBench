#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct intel_engine_execlists {struct execlist_port* port; } ;
struct intel_engine_cs {struct intel_engine_execlists execlists; } ;
struct i915_request {int dummy; } ;
struct execlist_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXECLISTS_ACTIVE_PREEMPT ; 
 scalar_t__ GUC_PREEMPT_FINISHED ; 
 int /*<<< orphan*/  I915_GEM_HWS_PREEMPT_INDEX ; 
 int /*<<< orphan*/  complete_preempt_context (struct intel_engine_cs* const) ; 
 scalar_t__ execlists_is_active (struct intel_engine_execlists* const,int /*<<< orphan*/ ) ; 
 struct execlist_port* execlists_port_complete (struct intel_engine_execlists* const,struct execlist_port*) ; 
 int /*<<< orphan*/  execlists_user_begin (struct intel_engine_execlists* const,struct execlist_port*) ; 
 int /*<<< orphan*/  execlists_user_end (struct intel_engine_execlists* const) ; 
 int /*<<< orphan*/  guc_dequeue (struct intel_engine_cs* const) ; 
 scalar_t__ i915_request_completed (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_put (struct i915_request*) ; 
 scalar_t__ intel_read_status_page (struct intel_engine_cs* const,int /*<<< orphan*/ ) ; 
 scalar_t__ port_isset (struct execlist_port*) ; 
 struct i915_request* port_request (struct execlist_port*) ; 
 int /*<<< orphan*/  trace_i915_request_out (struct i915_request*) ; 

__attribute__((used)) static void guc_submission_tasklet(unsigned long data)
{
	struct intel_engine_cs * const engine = (struct intel_engine_cs *)data;
	struct intel_engine_execlists * const execlists = &engine->execlists;
	struct execlist_port *port = execlists->port;
	struct i915_request *rq;

	rq = port_request(port);
	while (rq && i915_request_completed(rq)) {
		trace_i915_request_out(rq);
		i915_request_put(rq);

		port = execlists_port_complete(execlists, port);
		if (port_isset(port)) {
			execlists_user_begin(execlists, port);
			rq = port_request(port);
		} else {
			execlists_user_end(execlists);
			rq = NULL;
		}
	}

	if (execlists_is_active(execlists, EXECLISTS_ACTIVE_PREEMPT) &&
	    intel_read_status_page(engine, I915_GEM_HWS_PREEMPT_INDEX) ==
	    GUC_PREEMPT_FINISHED)
		complete_preempt_context(engine);

	if (!execlists_is_active(execlists, EXECLISTS_ACTIVE_PREEMPT))
		guc_dequeue(engine);
}