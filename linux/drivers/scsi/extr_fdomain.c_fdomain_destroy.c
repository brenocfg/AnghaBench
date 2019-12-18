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
struct fdomain {int /*<<< orphan*/  work; } ;
struct Scsi_Host {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct fdomain*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 struct fdomain* shost_priv (struct Scsi_Host*) ; 

int fdomain_destroy(struct Scsi_Host *sh)
{
	struct fdomain *fd = shost_priv(sh);

	cancel_work_sync(&fd->work);
	scsi_remove_host(sh);
	if (sh->irq)
		free_irq(sh->irq, fd);
	scsi_host_put(sh);
	return 0;
}