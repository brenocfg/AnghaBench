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
struct TYPE_2__ {int reset; } ;
union zip_cmd_ctl {int u_reg64; TYPE_1__ s; } ;
struct zip_device {size_t index; scalar_t__ reg_base; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ ZIP_CMD_CTL ; 
 int ZIP_NUM_QUEUES ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct zip_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zip_cmd_qbuf_free (struct zip_device*,int) ; 
 int /*<<< orphan*/ ** zip_dev ; 
 int /*<<< orphan*/  zip_reg_write (int,scalar_t__) ; 

__attribute__((used)) static void zip_remove(struct pci_dev *pdev)
{
	struct zip_device *zip = pci_get_drvdata(pdev);
	union zip_cmd_ctl cmd_ctl;
	int q = 0;

	if (!zip)
		return;

	if (zip->reg_base) {
		cmd_ctl.u_reg64 = 0x0ull;
		cmd_ctl.s.reset = 1;  /* Forces ZIP cores to do reset */
		zip_reg_write(cmd_ctl.u_reg64, (zip->reg_base + ZIP_CMD_CTL));
		iounmap(zip->reg_base);
	}

	pci_release_regions(pdev);
	pci_disable_device(pdev);

	/*
	 * Free Command Queue buffers. This free should be called for all
	 * the enabled Queues.
	 */
	for (q = 0; q < ZIP_NUM_QUEUES; q++)
		zip_cmd_qbuf_free(zip, q);

	pci_set_drvdata(pdev, NULL);
	/* remove zip device from zip device list */
	zip_dev[zip->index] = NULL;
}