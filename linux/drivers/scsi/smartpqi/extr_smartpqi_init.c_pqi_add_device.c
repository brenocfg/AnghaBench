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
struct pqi_scsi_dev {int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  bus; } ;
struct pqi_ctrl_info {int /*<<< orphan*/  sas_host; int /*<<< orphan*/  scsi_host; } ;

/* Variables and functions */
 int pqi_add_sas_device (int /*<<< orphan*/ ,struct pqi_scsi_dev*) ; 
 scalar_t__ pqi_is_logical_device (struct pqi_scsi_dev*) ; 
 int scsi_add_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pqi_add_device(struct pqi_ctrl_info *ctrl_info,
	struct pqi_scsi_dev *device)
{
	int rc;

	if (pqi_is_logical_device(device))
		rc = scsi_add_device(ctrl_info->scsi_host, device->bus,
			device->target, device->lun);
	else
		rc = pqi_add_sas_device(ctrl_info->sas_host, device);

	return rc;
}