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
struct hpsa_scsi_dev_t {int /*<<< orphan*/  commands_outstanding; scalar_t__ in_reset; } ;
struct ctlr_info {int /*<<< orphan*/  event_sync_wait_queue; } ;
struct CommandList {int /*<<< orphan*/  scsi_cmd; struct hpsa_scsi_dev_t* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_CMD_IDLE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hpsa_cmd_resolve_events(struct ctlr_info *h,
		struct CommandList *c)
{
	struct hpsa_scsi_dev_t *dev = c->device;

	/*
	 * Reset c->scsi_cmd here so that the reset handler will know
	 * this command has completed.  Then, check to see if the handler is
	 * waiting for this command, and, if so, wake it.
	 */
	c->scsi_cmd = SCSI_CMD_IDLE;
	mb();	/* Declare command idle before checking for pending events. */
	if (dev) {
		atomic_dec(&dev->commands_outstanding);
		if (dev->in_reset &&
			atomic_read(&dev->commands_outstanding) <= 0)
			wake_up_all(&h->event_sync_wait_queue);
	}
}