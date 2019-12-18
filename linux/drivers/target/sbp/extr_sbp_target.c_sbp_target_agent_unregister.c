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
struct sbp_target_agent {int /*<<< orphan*/  work; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_core_remove_address_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct sbp_target_agent*) ; 

__attribute__((used)) static void sbp_target_agent_unregister(struct sbp_target_agent *agent)
{
	fw_core_remove_address_handler(&agent->handler);
	cancel_work_sync(&agent->work);
	kfree(agent);
}