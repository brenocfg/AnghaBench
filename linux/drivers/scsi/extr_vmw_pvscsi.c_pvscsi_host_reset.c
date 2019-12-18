#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_1__* device; } ;
struct pvscsi_adapter {int use_msg; int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  workqueue; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int SUCCESS ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ll_adapter_reset (struct pvscsi_adapter*) ; 
 int /*<<< orphan*/  pvscsi_process_completion_ring (struct pvscsi_adapter*) ; 
 int /*<<< orphan*/  pvscsi_process_request_ring (struct pvscsi_adapter*) ; 
 int /*<<< orphan*/  pvscsi_reset_all (struct pvscsi_adapter*) ; 
 int /*<<< orphan*/  pvscsi_setup_all_rings (struct pvscsi_adapter*) ; 
 int /*<<< orphan*/  pvscsi_unmask_intr (struct pvscsi_adapter*) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*) ; 
 struct pvscsi_adapter* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pvscsi_host_reset(struct scsi_cmnd *cmd)
{
	struct Scsi_Host *host = cmd->device->host;
	struct pvscsi_adapter *adapter = shost_priv(host);
	unsigned long flags;
	bool use_msg;

	scmd_printk(KERN_INFO, cmd, "SCSI Host reset\n");

	spin_lock_irqsave(&adapter->hw_lock, flags);

	use_msg = adapter->use_msg;

	if (use_msg) {
		adapter->use_msg = 0;
		spin_unlock_irqrestore(&adapter->hw_lock, flags);

		/*
		 * Now that we know that the ISR won't add more work on the
		 * workqueue we can safely flush any outstanding work.
		 */
		flush_workqueue(adapter->workqueue);
		spin_lock_irqsave(&adapter->hw_lock, flags);
	}

	/*
	 * We're going to tear down the entire ring structure and set it back
	 * up, so stalling new requests until all completions are flushed and
	 * the rings are back in place.
	 */

	pvscsi_process_request_ring(adapter);

	ll_adapter_reset(adapter);

	/*
	 * Now process any completions.  Note we do this AFTER adapter reset,
	 * which is strange, but stops races where completions get posted
	 * between processing the ring and issuing the reset.  The backend will
	 * not touch the ring memory after reset, so the immediately pre-reset
	 * completion ring state is still valid.
	 */
	pvscsi_process_completion_ring(adapter);

	pvscsi_reset_all(adapter);
	adapter->use_msg = use_msg;
	pvscsi_setup_all_rings(adapter);
	pvscsi_unmask_intr(adapter);

	spin_unlock_irqrestore(&adapter->hw_lock, flags);

	return SUCCESS;
}