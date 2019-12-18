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
struct myrs_hba {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  myrs_cleanup (struct myrs_hba*) ; 
 int /*<<< orphan*/  myrs_create_mempools (struct pci_dev*,struct myrs_hba*) ; 
 int /*<<< orphan*/  myrs_destroy_mempools (struct myrs_hba*) ; 
 struct myrs_hba* myrs_detect (struct pci_dev*,struct pci_device_id const*) ; 
 int myrs_get_config (struct myrs_hba*) ; 
 int scsi_add_host (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_scan_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
myrs_probe(struct pci_dev *dev, const struct pci_device_id *entry)
{
	struct myrs_hba *cs;
	int ret;

	cs = myrs_detect(dev, entry);
	if (!cs)
		return -ENODEV;

	ret = myrs_get_config(cs);
	if (ret < 0) {
		myrs_cleanup(cs);
		return ret;
	}

	if (!myrs_create_mempools(dev, cs)) {
		ret = -ENOMEM;
		goto failed;
	}

	ret = scsi_add_host(cs->host, &dev->dev);
	if (ret) {
		dev_err(&dev->dev, "scsi_add_host failed with %d\n", ret);
		myrs_destroy_mempools(cs);
		goto failed;
	}
	scsi_scan_host(cs->host);
	return 0;
failed:
	myrs_cleanup(cs);
	return ret;
}