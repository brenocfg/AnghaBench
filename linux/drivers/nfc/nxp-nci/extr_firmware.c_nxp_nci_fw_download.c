#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nxp_nci_fw_info {int /*<<< orphan*/  work; scalar_t__ cmd_result; scalar_t__ frame_size; scalar_t__ written; TYPE_4__* fw; int /*<<< orphan*/  size; int /*<<< orphan*/  data; int /*<<< orphan*/  name; } ;
struct nxp_nci_info {int /*<<< orphan*/  info_lock; int /*<<< orphan*/  mode; int /*<<< orphan*/  phy_id; TYPE_3__* phy_ops; struct nxp_nci_fw_info fw_info; } ;
struct nci_dev {TYPE_2__* nfc_dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int (* set_mode ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  write; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct TYPE_7__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  NXP_NCI_MODE_FW ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nxp_nci_info* nci_get_drvdata (struct nci_dev*) ; 
 int /*<<< orphan*/  release_firmware (TYPE_4__*) ; 
 int request_firmware (TYPE_4__**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nxp_nci_fw_download(struct nci_dev *ndev, const char *firmware_name)
{
	struct nxp_nci_info *info = nci_get_drvdata(ndev);
	struct nxp_nci_fw_info *fw_info = &info->fw_info;
	int r;

	mutex_lock(&info->info_lock);

	if (!info->phy_ops->set_mode || !info->phy_ops->write) {
		r = -ENOTSUPP;
		goto fw_download_exit;
	}

	if (!firmware_name || firmware_name[0] == '\0') {
		r = -EINVAL;
		goto fw_download_exit;
	}

	strcpy(fw_info->name, firmware_name);

	r = request_firmware(&fw_info->fw, firmware_name,
			     ndev->nfc_dev->dev.parent);
	if (r < 0)
		goto fw_download_exit;

	r = info->phy_ops->set_mode(info->phy_id, NXP_NCI_MODE_FW);
	if (r < 0) {
		release_firmware(fw_info->fw);
		goto fw_download_exit;
	}

	info->mode = NXP_NCI_MODE_FW;

	fw_info->data = fw_info->fw->data;
	fw_info->size = fw_info->fw->size;
	fw_info->written = 0;
	fw_info->frame_size = 0;
	fw_info->cmd_result = 0;

	schedule_work(&fw_info->work);

fw_download_exit:
	mutex_unlock(&info->info_lock);
	return r;
}