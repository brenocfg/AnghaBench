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
typedef  int u32 ;
typedef  int u16 ;
struct qca_version {int /*<<< orphan*/  patch_version; int /*<<< orphan*/  rom_version; } ;
struct qca_rampatch_version {int /*<<< orphan*/  patch_version; int /*<<< orphan*/  rom_version; } ;
struct qca_device_info {int /*<<< orphan*/  rampatch_hdr; scalar_t__ ver_offset; } ;
struct hci_dev {int /*<<< orphan*/  dev; } ;
struct firmware {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  fwname ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,...) ; 
 int /*<<< orphan*/  bt_dev_info (struct hci_dev*,char*,...) ; 
 int btusb_setup_qca_download_fw (struct hci_dev*,struct firmware const*,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int btusb_setup_qca_load_rampatch(struct hci_dev *hdev,
					 struct qca_version *ver,
					 const struct qca_device_info *info)
{
	struct qca_rampatch_version *rver;
	const struct firmware *fw;
	u32 ver_rom, ver_patch;
	u16 rver_rom, rver_patch;
	char fwname[64];
	int err;

	ver_rom = le32_to_cpu(ver->rom_version);
	ver_patch = le32_to_cpu(ver->patch_version);

	snprintf(fwname, sizeof(fwname), "qca/rampatch_usb_%08x.bin", ver_rom);

	err = request_firmware(&fw, fwname, &hdev->dev);
	if (err) {
		bt_dev_err(hdev, "failed to request rampatch file: %s (%d)",
			   fwname, err);
		return err;
	}

	bt_dev_info(hdev, "using rampatch file: %s", fwname);

	rver = (struct qca_rampatch_version *)(fw->data + info->ver_offset);
	rver_rom = le16_to_cpu(rver->rom_version);
	rver_patch = le16_to_cpu(rver->patch_version);

	bt_dev_info(hdev, "QCA: patch rome 0x%x build 0x%x, "
		    "firmware rome 0x%x build 0x%x",
		    rver_rom, rver_patch, ver_rom, ver_patch);

	if (rver_rom != ver_rom || rver_patch <= ver_patch) {
		bt_dev_err(hdev, "rampatch file version did not match with firmware");
		err = -EINVAL;
		goto done;
	}

	err = btusb_setup_qca_download_fw(hdev, fw, info->rampatch_hdr);

done:
	release_firmware(fw);

	return err;
}