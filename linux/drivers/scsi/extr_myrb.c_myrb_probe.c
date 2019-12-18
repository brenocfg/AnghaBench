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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct myrb_hba {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  myrb_cleanup (struct myrb_hba*) ; 
 int /*<<< orphan*/  myrb_create_mempools (struct pci_dev*,struct myrb_hba*) ; 
 int /*<<< orphan*/  myrb_destroy_mempools (struct myrb_hba*) ; 
 struct myrb_hba* myrb_detect (struct pci_dev*,struct pci_device_id const*) ; 
 int myrb_get_hba_config (struct myrb_hba*) ; 
 int scsi_add_host (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_scan_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int myrb_probe(struct pci_dev *dev, const struct pci_device_id *entry)
{
	struct myrb_hba *cb;
	int ret;

	cb = myrb_detect(dev, entry);
	if (!cb)
		return -ENODEV;

	ret = myrb_get_hba_config(cb);
	if (ret < 0) {
		myrb_cleanup(cb);
		return ret;
	}

	if (!myrb_create_mempools(dev, cb)) {
		ret = -ENOMEM;
		goto failed;
	}

	ret = scsi_add_host(cb->host, &dev->dev);
	if (ret) {
		dev_err(&dev->dev, "scsi_add_host failed with %d\n", ret);
		myrb_destroy_mempools(cb);
		goto failed;
	}
	scsi_scan_host(cb->host);
	return 0;
failed:
	myrb_cleanup(cb);
	return ret;
}