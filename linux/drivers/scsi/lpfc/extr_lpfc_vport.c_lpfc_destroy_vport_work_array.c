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
struct lpfc_vport {int dummy; } ;
struct lpfc_hba {int max_vports; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct lpfc_vport**) ; 
 int /*<<< orphan*/  lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 

void
lpfc_destroy_vport_work_array(struct lpfc_hba *phba, struct lpfc_vport **vports)
{
	int i;
	if (vports == NULL)
		return;
	for (i = 0; i <= phba->max_vports && vports[i] != NULL; i++)
		scsi_host_put(lpfc_shost_from_vport(vports[i]));
	kfree(vports);
}