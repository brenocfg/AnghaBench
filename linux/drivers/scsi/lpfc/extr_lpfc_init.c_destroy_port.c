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
struct lpfc_vport {int /*<<< orphan*/  listentry; struct lpfc_hba* phba; } ;
struct lpfc_hba {int /*<<< orphan*/  port_list_lock; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fc_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_cleanup (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_debugfs_terminate (struct lpfc_vport*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void
destroy_port(struct lpfc_vport *vport)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	struct lpfc_hba  *phba = vport->phba;

	lpfc_debugfs_terminate(vport);
	fc_remove_host(shost);
	scsi_remove_host(shost);

	spin_lock_irq(&phba->port_list_lock);
	list_del_init(&vport->listentry);
	spin_unlock_irq(&phba->port_list_lock);

	lpfc_cleanup(vport);
	return;
}