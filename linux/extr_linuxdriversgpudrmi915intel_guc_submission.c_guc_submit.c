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
struct intel_guc {int dummy; } ;
struct intel_engine_execlists {struct execlist_port* port; } ;
struct intel_engine_cs {struct intel_engine_execlists execlists; TYPE_2__* i915; } ;
struct i915_request {TYPE_1__* ring; } ;
struct execlist_port {int dummy; } ;
struct TYPE_4__ {struct intel_guc guc; } ;
struct TYPE_3__ {int /*<<< orphan*/  vma; } ;

/* Variables and functions */
 unsigned int execlists_num_ports (struct intel_engine_execlists* const) ; 
 int /*<<< orphan*/  flush_ggtt_writes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  guc_add_request (struct intel_guc*,struct i915_request*) ; 
 int /*<<< orphan*/  port_pack (struct i915_request*,unsigned int) ; 
 int /*<<< orphan*/  port_set (struct execlist_port*,int /*<<< orphan*/ ) ; 
 struct i915_request* port_unpack (struct execlist_port*,unsigned int*) ; 

__attribute__((used)) static void guc_submit(struct intel_engine_cs *engine)
{
	struct intel_guc *guc = &engine->i915->guc;
	struct intel_engine_execlists * const execlists = &engine->execlists;
	struct execlist_port *port = execlists->port;
	unsigned int n;

	for (n = 0; n < execlists_num_ports(execlists); n++) {
		struct i915_request *rq;
		unsigned int count;

		rq = port_unpack(&port[n], &count);
		if (rq && count == 0) {
			port_set(&port[n], port_pack(rq, ++count));

			flush_ggtt_writes(rq->ring->vma);

			guc_add_request(guc, rq);
		}
	}
}