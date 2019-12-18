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
struct scsi_device {int dummy; } ;
struct mvumi_sgl {int dummy; } ;
struct mvumi_msg_frame {int dummy; } ;
struct mvumi_hba {int ib_max_size; int max_io; unsigned int max_sge; int max_transfer_size; struct Scsi_Host* shost; scalar_t__ max_target_id; TYPE_1__* pdev; int /*<<< orphan*/  sas_discovery_mutex; int /*<<< orphan*/  dm_thread; int /*<<< orphan*/  pnp_count; int /*<<< orphan*/  fw_flag; int /*<<< orphan*/  unique_id; } ;
struct Scsi_Host {int can_queue; unsigned int sg_tablesize; int max_sectors; int cmd_per_lun; int /*<<< orphan*/  max_cmd_len; scalar_t__ max_id; int /*<<< orphan*/  unique_id; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {scalar_t__ device; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_COMMAND_SIZE ; 
 int /*<<< orphan*/  MVUMI_FW_ATTACH ; 
 scalar_t__ PCI_DEVICE_ID_MARVELL_MV9580 ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kthread_create (int /*<<< orphan*/ ,struct mvumi_hba*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvumi_rescan_bus ; 
 int scsi_add_device (struct Scsi_Host*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int scsi_add_host (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 struct scsi_device* scsi_device_lookup (struct Scsi_Host*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_device_put (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_remove_device (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvumi_io_attach(struct mvumi_hba *mhba)
{
	struct Scsi_Host *host = mhba->shost;
	struct scsi_device *sdev = NULL;
	int ret;
	unsigned int max_sg = (mhba->ib_max_size + 4 -
		sizeof(struct mvumi_msg_frame)) / sizeof(struct mvumi_sgl);

	host->irq = mhba->pdev->irq;
	host->unique_id = mhba->unique_id;
	host->can_queue = (mhba->max_io - 1) ? (mhba->max_io - 1) : 1;
	host->sg_tablesize = mhba->max_sge > max_sg ? max_sg : mhba->max_sge;
	host->max_sectors = mhba->max_transfer_size / 512;
	host->cmd_per_lun = (mhba->max_io - 1) ? (mhba->max_io - 1) : 1;
	host->max_id = mhba->max_target_id;
	host->max_cmd_len = MAX_COMMAND_SIZE;

	ret = scsi_add_host(host, &mhba->pdev->dev);
	if (ret) {
		dev_err(&mhba->pdev->dev, "scsi_add_host failed\n");
		return ret;
	}
	mhba->fw_flag |= MVUMI_FW_ATTACH;

	mutex_lock(&mhba->sas_discovery_mutex);
	if (mhba->pdev->device == PCI_DEVICE_ID_MARVELL_MV9580)
		ret = scsi_add_device(host, 0, mhba->max_target_id - 1, 0);
	else
		ret = 0;
	if (ret) {
		dev_err(&mhba->pdev->dev, "add virtual device failed\n");
		mutex_unlock(&mhba->sas_discovery_mutex);
		goto fail_add_device;
	}

	mhba->dm_thread = kthread_create(mvumi_rescan_bus,
						mhba, "mvumi_scanthread");
	if (IS_ERR(mhba->dm_thread)) {
		dev_err(&mhba->pdev->dev,
			"failed to create device scan thread\n");
		mutex_unlock(&mhba->sas_discovery_mutex);
		goto fail_create_thread;
	}
	atomic_set(&mhba->pnp_count, 1);
	wake_up_process(mhba->dm_thread);

	mutex_unlock(&mhba->sas_discovery_mutex);
	return 0;

fail_create_thread:
	if (mhba->pdev->device == PCI_DEVICE_ID_MARVELL_MV9580)
		sdev = scsi_device_lookup(mhba->shost, 0,
						mhba->max_target_id - 1, 0);
	if (sdev) {
		scsi_remove_device(sdev);
		scsi_device_put(sdev);
	}
fail_add_device:
	scsi_remove_host(mhba->shost);
	return ret;
}