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
struct intel_engine_execlists {int port_mask; int /*<<< orphan*/  queue; int /*<<< orphan*/  queue_priority_hint; int /*<<< orphan*/  inflight; int /*<<< orphan*/  active; int /*<<< orphan*/  pending; } ;
struct intel_engine_cs {struct intel_engine_execlists execlists; } ;

/* Variables and functions */
 scalar_t__ EXECLIST_MAX_PORTS ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  INT_MIN ; 
 int /*<<< orphan*/  RB_ROOT_CACHED ; 
 scalar_t__ execlists_num_ports (struct intel_engine_execlists* const) ; 
 int /*<<< orphan*/  is_power_of_2 (scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void intel_engine_init_execlists(struct intel_engine_cs *engine)
{
	struct intel_engine_execlists * const execlists = &engine->execlists;

	execlists->port_mask = 1;
	GEM_BUG_ON(!is_power_of_2(execlists_num_ports(execlists)));
	GEM_BUG_ON(execlists_num_ports(execlists) > EXECLIST_MAX_PORTS);

	memset(execlists->pending, 0, sizeof(execlists->pending));
	execlists->active =
		memset(execlists->inflight, 0, sizeof(execlists->inflight));

	execlists->queue_priority_hint = INT_MIN;
	execlists->queue = RB_ROOT_CACHED;
}