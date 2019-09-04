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
struct intel_engine_execlists {int port_mask; int /*<<< orphan*/  queue; int /*<<< orphan*/  queue_priority; } ;
struct intel_engine_cs {struct intel_engine_execlists execlists; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON_NOT_POWER_OF_2 (scalar_t__) ; 
 scalar_t__ EXECLIST_MAX_PORTS ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  INT_MIN ; 
 int /*<<< orphan*/  RB_ROOT_CACHED ; 
 scalar_t__ execlists_num_ports (struct intel_engine_execlists* const) ; 

__attribute__((used)) static void intel_engine_init_execlist(struct intel_engine_cs *engine)
{
	struct intel_engine_execlists * const execlists = &engine->execlists;

	execlists->port_mask = 1;
	BUILD_BUG_ON_NOT_POWER_OF_2(execlists_num_ports(execlists));
	GEM_BUG_ON(execlists_num_ports(execlists) > EXECLIST_MAX_PORTS);

	execlists->queue_priority = INT_MIN;
	execlists->queue = RB_ROOT_CACHED;
}