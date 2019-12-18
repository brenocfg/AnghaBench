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
struct pqi_ctrl_info {struct Scsi_Host* scsi_host; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pqi_delete_sas_host (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 

__attribute__((used)) static void pqi_unregister_scsi(struct pqi_ctrl_info *ctrl_info)
{
	struct Scsi_Host *shost;

	pqi_delete_sas_host(ctrl_info);

	shost = ctrl_info->scsi_host;
	if (!shost)
		return;

	scsi_remove_host(shost);
	scsi_host_put(shost);
}