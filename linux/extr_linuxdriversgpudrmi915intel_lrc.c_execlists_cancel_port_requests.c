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
struct intel_engine_execlists {int /*<<< orphan*/  active; struct execlist_port* port; } ;
struct TYPE_3__ {int /*<<< orphan*/  seqno; int /*<<< orphan*/  context; } ;
struct i915_request {TYPE_2__* engine; TYPE_1__ fence; int /*<<< orphan*/  global_seqno; } ;
struct execlist_port {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTEL_CONTEXT_SCHEDULE_OUT ; 
 int /*<<< orphan*/  INTEL_CONTEXT_SCHEDULE_PREEMPTED ; 
 int /*<<< orphan*/  execlists_clear_all_active (struct intel_engine_execlists* const) ; 
 int /*<<< orphan*/  execlists_context_schedule_out (struct i915_request*,int /*<<< orphan*/ ) ; 
 unsigned int execlists_num_ports (struct intel_engine_execlists* const) ; 
 scalar_t__ i915_request_completed (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_put (struct i915_request*) ; 
 int /*<<< orphan*/  intel_engine_get_seqno (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (struct execlist_port*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ port_isset (struct execlist_port*) ; 
 struct i915_request* port_request (struct execlist_port*) ; 

void
execlists_cancel_port_requests(struct intel_engine_execlists * const execlists)
{
	struct execlist_port *port = execlists->port;
	unsigned int num_ports = execlists_num_ports(execlists);

	while (num_ports-- && port_isset(port)) {
		struct i915_request *rq = port_request(port);

		GEM_TRACE("%s:port%u global=%d (fence %llx:%d), (current %d)\n",
			  rq->engine->name,
			  (unsigned int)(port - execlists->port),
			  rq->global_seqno,
			  rq->fence.context, rq->fence.seqno,
			  intel_engine_get_seqno(rq->engine));

		GEM_BUG_ON(!execlists->active);
		execlists_context_schedule_out(rq,
					       i915_request_completed(rq) ?
					       INTEL_CONTEXT_SCHEDULE_OUT :
					       INTEL_CONTEXT_SCHEDULE_PREEMPTED);

		i915_request_put(rq);

		memset(port, 0, sizeof(*port));
		port++;
	}

	execlists_clear_all_active(execlists);
}