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
struct scsi_device {int /*<<< orphan*/  list_lock; int /*<<< orphan*/  cmd_list; struct Scsi_Host* host; } ;
struct scsi_cmnd {int /*<<< orphan*/  list; struct scsi_device* device; } ;
struct Scsi_Host {scalar_t__ use_cmd_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void scsi_add_cmd_to_list(struct scsi_cmnd *cmd)
{
	struct scsi_device *sdev = cmd->device;
	struct Scsi_Host *shost = sdev->host;
	unsigned long flags;

	if (shost->use_cmd_list) {
		spin_lock_irqsave(&sdev->list_lock, flags);
		list_add_tail(&cmd->list, &sdev->cmd_list);
		spin_unlock_irqrestore(&sdev->list_lock, flags);
	}
}