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
struct pqi_ctrl_info {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 scalar_t__ pqi_ctrl_in_ofa (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_scan_scsi_devices (struct pqi_ctrl_info*) ; 
 struct pqi_ctrl_info* shost_to_hba (struct Scsi_Host*) ; 

__attribute__((used)) static void pqi_scan_start(struct Scsi_Host *shost)
{
	struct pqi_ctrl_info *ctrl_info;

	ctrl_info = shost_to_hba(shost);
	if (pqi_ctrl_in_ofa(ctrl_info))
		return;

	pqi_scan_scsi_devices(ctrl_info);
}