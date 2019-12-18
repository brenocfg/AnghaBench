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
struct hisi_hba {int /*<<< orphan*/  flags; int /*<<< orphan*/  sem; TYPE_1__* hw; int /*<<< orphan*/  debugfs_work; int /*<<< orphan*/  wq; scalar_t__ debugfs_itct; struct Scsi_Host* shost; struct device* dev; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {int (* soft_reset ) (struct hisi_hba*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HISI_SAS_REJECT_CMD_BIT ; 
 int /*<<< orphan*/  HISI_SAS_RESET_BIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int /*<<< orphan*/  hisi_sas_controller_reset_done (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_controller_reset_prepare (struct hisi_hba*) ; 
 scalar_t__ hisi_sas_debugfs_enable ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_unblock_requests (struct Scsi_Host*) ; 
 int stub1 (struct hisi_hba*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hisi_sas_controller_reset(struct hisi_hba *hisi_hba)
{
	struct device *dev = hisi_hba->dev;
	struct Scsi_Host *shost = hisi_hba->shost;
	int rc;

	if (hisi_sas_debugfs_enable && hisi_hba->debugfs_itct)
		queue_work(hisi_hba->wq, &hisi_hba->debugfs_work);

	if (!hisi_hba->hw->soft_reset)
		return -1;

	if (test_and_set_bit(HISI_SAS_RESET_BIT, &hisi_hba->flags))
		return -1;

	dev_info(dev, "controller resetting...\n");
	hisi_sas_controller_reset_prepare(hisi_hba);

	rc = hisi_hba->hw->soft_reset(hisi_hba);
	if (rc) {
		dev_warn(dev, "controller reset failed (%d)\n", rc);
		clear_bit(HISI_SAS_REJECT_CMD_BIT, &hisi_hba->flags);
		up(&hisi_hba->sem);
		scsi_unblock_requests(shost);
		clear_bit(HISI_SAS_RESET_BIT, &hisi_hba->flags);
		return rc;
	}

	hisi_sas_controller_reset_done(hisi_hba);
	dev_info(dev, "controller reset complete\n");

	return 0;
}