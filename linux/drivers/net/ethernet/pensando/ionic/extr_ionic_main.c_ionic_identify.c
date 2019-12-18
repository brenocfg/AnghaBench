#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  driver_ver_str; int /*<<< orphan*/  os_type; } ;
struct ionic_identity {int /*<<< orphan*/  dev; TYPE_2__ drv; } ;
struct ionic_dev {TYPE_1__* dev_cmd_regs; } ;
struct ionic {int /*<<< orphan*/  dev_cmd_lock; struct ionic_dev idev; struct ionic_identity ident; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVCMD_TIMEOUT ; 
 int /*<<< orphan*/  IONIC_DRV_VERSION ; 
 int /*<<< orphan*/  IONIC_IDENTITY_VERSION_1 ; 
 int /*<<< orphan*/  IONIC_OS_TYPE_LINUX ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ionic_debugfs_add_ident (struct ionic*) ; 
 int /*<<< orphan*/  ionic_dev_cmd_identify (struct ionic_dev*,int /*<<< orphan*/ ) ; 
 int ionic_dev_cmd_wait (struct ionic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memcpy_toio (int /*<<< orphan*/ *,TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  memset (struct ionic_identity*,int /*<<< orphan*/ ,int) ; 
 size_t min (int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int ionic_identify(struct ionic *ionic)
{
	struct ionic_identity *ident = &ionic->ident;
	struct ionic_dev *idev = &ionic->idev;
	size_t sz;
	int err;

	memset(ident, 0, sizeof(*ident));

	ident->drv.os_type = cpu_to_le32(IONIC_OS_TYPE_LINUX);
	strncpy(ident->drv.driver_ver_str, IONIC_DRV_VERSION,
		sizeof(ident->drv.driver_ver_str) - 1);

	mutex_lock(&ionic->dev_cmd_lock);

	sz = min(sizeof(ident->drv), sizeof(idev->dev_cmd_regs->data));
	memcpy_toio(&idev->dev_cmd_regs->data, &ident->drv, sz);

	ionic_dev_cmd_identify(idev, IONIC_IDENTITY_VERSION_1);
	err = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
	if (!err) {
		sz = min(sizeof(ident->dev), sizeof(idev->dev_cmd_regs->data));
		memcpy_fromio(&ident->dev, &idev->dev_cmd_regs->data, sz);
	}

	mutex_unlock(&ionic->dev_cmd_lock);

	if (err)
		goto err_out_unmap;

	ionic_debugfs_add_ident(ionic);

	return 0;

err_out_unmap:
	return err;
}