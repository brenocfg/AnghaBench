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
struct pvscsi_adapter {int /*<<< orphan*/  hw_lock; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ll_bus_reset (struct pvscsi_adapter*) ; 
 int /*<<< orphan*/  pvscsi_process_completion_ring (struct pvscsi_adapter*) ; 
 int /*<<< orphan*/  pvscsi_process_request_ring (struct pvscsi_adapter*) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*) ; 
 struct pvscsi_adapter* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pvscsi_bus_reset(struct scsi_cmnd *cmd)
{
	struct Scsi_Host *host = cmd->device->host;
	struct pvscsi_adapter *adapter = shost_priv(host);
	unsigned long flags;

	scmd_printk(KERN_INFO, cmd, "SCSI Bus reset\n");

	/*
	 * We don't want to queue new requests for this bus after
	 * flushing all pending requests to emulation, since new
	 * requests could then sneak in during this bus reset phase,
	 * so take the lock now.
	 */
	spin_lock_irqsave(&adapter->hw_lock, flags);

	pvscsi_process_request_ring(adapter);
	ll_bus_reset(adapter);
	pvscsi_process_completion_ring(adapter);

	spin_unlock_irqrestore(&adapter->hw_lock, flags);

	return SUCCESS;
}