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
struct vmballoon {int capabilities; int batch_max_pages; int reset_required; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int VMW_BALLOON_BASIC_CMDS ; 
 int VMW_BALLOON_BATCHED_CMDS ; 
 int VMW_BALLOON_BATCH_MAX_PAGES ; 
 int /*<<< orphan*/  VMW_BALLOON_CAPABILITIES ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  vmballoon_basic_ops ; 
 int /*<<< orphan*/  vmballoon_batched_ops ; 
 int /*<<< orphan*/  vmballoon_init_batching (struct vmballoon*) ; 
 int /*<<< orphan*/  vmballoon_pop (struct vmballoon*) ; 
 int /*<<< orphan*/  vmballoon_send_guest_id (struct vmballoon*) ; 
 int /*<<< orphan*/  vmballoon_send_start (struct vmballoon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmballoon_vmci_cleanup (struct vmballoon*) ; 
 int vmballoon_vmci_init (struct vmballoon*) ; 

__attribute__((used)) static void vmballoon_reset(struct vmballoon *b)
{
	int error;

	vmballoon_vmci_cleanup(b);

	/* free all pages, skipping monitor unlock */
	vmballoon_pop(b);

	if (!vmballoon_send_start(b, VMW_BALLOON_CAPABILITIES))
		return;

	if ((b->capabilities & VMW_BALLOON_BATCHED_CMDS) != 0) {
		b->ops = &vmballoon_batched_ops;
		b->batch_max_pages = VMW_BALLOON_BATCH_MAX_PAGES;
		if (!vmballoon_init_batching(b)) {
			/*
			 * We failed to initialize batching, inform the monitor
			 * about it by sending a null capability.
			 *
			 * The guest will retry in one second.
			 */
			vmballoon_send_start(b, 0);
			return;
		}
	} else if ((b->capabilities & VMW_BALLOON_BASIC_CMDS) != 0) {
		b->ops = &vmballoon_basic_ops;
		b->batch_max_pages = 1;
	}

	b->reset_required = false;

	error = vmballoon_vmci_init(b);
	if (error)
		pr_err("failed to initialize vmci doorbell\n");

	if (!vmballoon_send_guest_id(b))
		pr_err("failed to send guest ID to the host\n");
}