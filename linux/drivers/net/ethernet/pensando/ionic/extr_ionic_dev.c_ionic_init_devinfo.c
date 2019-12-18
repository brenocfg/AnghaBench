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
struct TYPE_4__ {scalar_t__* fw_version; scalar_t__* serial_num; void* asic_rev; void* asic_type; } ;
struct ionic_dev {TYPE_2__ dev_info; TYPE_1__* dev_info_regs; } ;
struct ionic {int /*<<< orphan*/  dev; struct ionic_dev idev; } ;
struct TYPE_3__ {int /*<<< orphan*/  serial_num; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  asic_rev; int /*<<< orphan*/  asic_type; } ;

/* Variables and functions */
 size_t IONIC_DEVINFO_FWVERS_BUFLEN ; 
 size_t IONIC_DEVINFO_SERIAL_BUFLEN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 void* ioread8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy_fromio (scalar_t__*,int /*<<< orphan*/ ,size_t) ; 

void ionic_init_devinfo(struct ionic *ionic)
{
	struct ionic_dev *idev = &ionic->idev;

	idev->dev_info.asic_type = ioread8(&idev->dev_info_regs->asic_type);
	idev->dev_info.asic_rev = ioread8(&idev->dev_info_regs->asic_rev);

	memcpy_fromio(idev->dev_info.fw_version,
		      idev->dev_info_regs->fw_version,
		      IONIC_DEVINFO_FWVERS_BUFLEN);

	memcpy_fromio(idev->dev_info.serial_num,
		      idev->dev_info_regs->serial_num,
		      IONIC_DEVINFO_SERIAL_BUFLEN);

	idev->dev_info.fw_version[IONIC_DEVINFO_FWVERS_BUFLEN] = 0;
	idev->dev_info.serial_num[IONIC_DEVINFO_SERIAL_BUFLEN] = 0;

	dev_dbg(ionic->dev, "fw_version %s\n", idev->dev_info.fw_version);
}