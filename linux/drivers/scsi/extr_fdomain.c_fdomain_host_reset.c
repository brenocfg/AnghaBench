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
struct fdomain {int /*<<< orphan*/  base; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_2__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int SUCCESS ; 
 int /*<<< orphan*/  fdomain_reset (int /*<<< orphan*/ ) ; 
 struct fdomain* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int fdomain_host_reset(struct scsi_cmnd *cmd)
{
	struct Scsi_Host *sh = cmd->device->host;
	struct fdomain *fd = shost_priv(sh);
	unsigned long flags;

	spin_lock_irqsave(sh->host_lock, flags);
	fdomain_reset(fd->base);
	spin_unlock_irqrestore(sh->host_lock, flags);
	return SUCCESS;
}