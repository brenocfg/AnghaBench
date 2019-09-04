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
struct intel_engine_execlists {int /*<<< orphan*/ * port; } ;
struct intel_engine_cs {struct intel_engine_execlists execlists; } ;
struct i915_request {int dummy; } ;
struct drm_i915_error_engine {unsigned int num_ports; int /*<<< orphan*/ * execlist; } ;

/* Variables and functions */
 unsigned int execlists_num_ports (struct intel_engine_execlists const* const) ; 
 struct i915_request* port_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record_request (struct i915_request*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void error_record_engine_execlists(struct intel_engine_cs *engine,
					  struct drm_i915_error_engine *ee)
{
	const struct intel_engine_execlists * const execlists = &engine->execlists;
	unsigned int n;

	for (n = 0; n < execlists_num_ports(execlists); n++) {
		struct i915_request *rq = port_request(&execlists->port[n]);

		if (!rq)
			break;

		record_request(rq, &ee->execlist[n]);
	}

	ee->num_ports = n;
}