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
struct nes_cm_core {int /*<<< orphan*/  node_cnt; int /*<<< orphan*/  listen_node_cnt; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NES_DBG_CM ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void print_core(struct nes_cm_core *core)
{
	nes_debug(NES_DBG_CM, "---------------------------------------------\n");
	nes_debug(NES_DBG_CM, "CM Core  -- (core = %p )\n", core);
	if (!core)
		return;
	nes_debug(NES_DBG_CM, "---------------------------------------------\n");

	nes_debug(NES_DBG_CM, "State         : %u \n", core->state);

	nes_debug(NES_DBG_CM, "Listen Nodes  : %u \n", atomic_read(&core->listen_node_cnt));
	nes_debug(NES_DBG_CM, "Active Nodes  : %u \n", atomic_read(&core->node_cnt));

	nes_debug(NES_DBG_CM, "core          : %p \n", core);

	nes_debug(NES_DBG_CM, "-------------- end core ---------------\n");
}