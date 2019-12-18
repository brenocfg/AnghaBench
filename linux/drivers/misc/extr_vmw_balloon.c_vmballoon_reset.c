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
struct vmballoon {int capabilities; int reset_required; int /*<<< orphan*/  conf_sem; } ;

/* Variables and functions */
 int VMW_BALLOON_BASIC_CMDS ; 
 int VMW_BALLOON_BATCHED_CMDS ; 
 int /*<<< orphan*/  VMW_BALLOON_CAPABILITIES ; 
 int /*<<< orphan*/  VMW_BALLOON_STAT_RESET ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmballoon_deinit_batching (struct vmballoon*) ; 
 scalar_t__ vmballoon_init_batching (struct vmballoon*) ; 
 int /*<<< orphan*/  vmballoon_pop (struct vmballoon*) ; 
 scalar_t__ vmballoon_send_guest_id (struct vmballoon*) ; 
 int /*<<< orphan*/  vmballoon_send_start (struct vmballoon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmballoon_stats_gen_inc (struct vmballoon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmballoon_vmci_cleanup (struct vmballoon*) ; 
 int vmballoon_vmci_init (struct vmballoon*) ; 

__attribute__((used)) static void vmballoon_reset(struct vmballoon *b)
{
	int error;

	down_write(&b->conf_sem);

	vmballoon_vmci_cleanup(b);

	/* free all pages, skipping monitor unlock */
	vmballoon_pop(b);

	if (vmballoon_send_start(b, VMW_BALLOON_CAPABILITIES))
		goto unlock;

	if ((b->capabilities & VMW_BALLOON_BATCHED_CMDS) != 0) {
		if (vmballoon_init_batching(b)) {
			/*
			 * We failed to initialize batching, inform the monitor
			 * about it by sending a null capability.
			 *
			 * The guest will retry in one second.
			 */
			vmballoon_send_start(b, 0);
			goto unlock;
		}
	} else if ((b->capabilities & VMW_BALLOON_BASIC_CMDS) != 0) {
		vmballoon_deinit_batching(b);
	}

	vmballoon_stats_gen_inc(b, VMW_BALLOON_STAT_RESET);
	b->reset_required = false;

	error = vmballoon_vmci_init(b);
	if (error)
		pr_err("failed to initialize vmci doorbell\n");

	if (vmballoon_send_guest_id(b))
		pr_err("failed to send guest ID to the host\n");

unlock:
	up_write(&b->conf_sem);
}