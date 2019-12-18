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
struct scsi_device {struct lpfc_device_data* hostdata; TYPE_1__* host; } ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_hba {int /*<<< orphan*/  devicelock; scalar_t__ cfg_fof; int /*<<< orphan*/  sdev_cnt; } ;
struct lpfc_device_data {int available; int /*<<< orphan*/  oas_enabled; } ;
struct TYPE_2__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_delete_device_data (struct lpfc_hba*,struct lpfc_device_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
lpfc_slave_destroy(struct scsi_device *sdev)
{
	struct lpfc_vport *vport = (struct lpfc_vport *) sdev->host->hostdata;
	struct lpfc_hba   *phba = vport->phba;
	unsigned long flags;
	struct lpfc_device_data *device_data = sdev->hostdata;

	atomic_dec(&phba->sdev_cnt);
	if ((phba->cfg_fof) && (device_data)) {
		spin_lock_irqsave(&phba->devicelock, flags);
		device_data->available = false;
		if (!device_data->oas_enabled)
			lpfc_delete_device_data(phba, device_data);
		spin_unlock_irqrestore(&phba->devicelock, flags);
	}
	sdev->hostdata = NULL;
	return;
}