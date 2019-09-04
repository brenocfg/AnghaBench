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
struct qca_version {int /*<<< orphan*/  rom_version; } ;
struct qca_device_info {int /*<<< orphan*/  nvm_hdr; } ;
struct hci_dev {int /*<<< orphan*/  dev; } ;
struct firmware {int dummy; } ;
typedef  int /*<<< orphan*/  fwname ;

/* Variables and functions */
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,char*,int) ; 
 int /*<<< orphan*/  bt_dev_info (struct hci_dev*,char*,char*) ; 
 int btusb_setup_qca_download_fw (struct hci_dev*,struct firmware const*,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int btusb_setup_qca_load_nvm(struct hci_dev *hdev,
				    struct qca_version *ver,
				    const struct qca_device_info *info)
{
	const struct firmware *fw;
	char fwname[64];
	int err;

	snprintf(fwname, sizeof(fwname), "qca/nvm_usb_%08x.bin",
		 le32_to_cpu(ver->rom_version));

	err = request_firmware(&fw, fwname, &hdev->dev);
	if (err) {
		bt_dev_err(hdev, "failed to request NVM file: %s (%d)",
			   fwname, err);
		return err;
	}

	bt_dev_info(hdev, "using NVM file: %s", fwname);

	err = btusb_setup_qca_download_fw(hdev, fw, info->nvm_hdr);

	release_firmware(fw);

	return err;
}