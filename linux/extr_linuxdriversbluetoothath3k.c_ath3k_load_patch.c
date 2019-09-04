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
struct usb_device {int /*<<< orphan*/  dev; } ;
struct firmware {scalar_t__ size; scalar_t__ data; } ;
struct ath3k_version {int /*<<< orphan*/  build_version; int /*<<< orphan*/  rom_version; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int ATH3K_NAME_LEN ; 
 unsigned char ATH3K_PATCH_UPDATE ; 
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  BT_ERR (char*,...) ; 
 int EINVAL ; 
 int ath3k_get_state (struct usb_device*,unsigned char*) ; 
 int ath3k_get_version (struct usb_device*,struct ath3k_version*) ; 
 int ath3k_load_fwfile (struct usb_device*,struct firmware const*) ; 
 scalar_t__ get_unaligned_le32 (scalar_t__) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 

__attribute__((used)) static int ath3k_load_patch(struct usb_device *udev)
{
	unsigned char fw_state;
	char filename[ATH3K_NAME_LEN];
	const struct firmware *firmware;
	struct ath3k_version fw_version;
	__u32 pt_rom_version, pt_build_version;
	int ret;

	ret = ath3k_get_state(udev, &fw_state);
	if (ret < 0) {
		BT_ERR("Can't get state to change to load ram patch err");
		return ret;
	}

	if (fw_state & ATH3K_PATCH_UPDATE) {
		BT_DBG("Patch was already downloaded");
		return 0;
	}

	ret = ath3k_get_version(udev, &fw_version);
	if (ret < 0) {
		BT_ERR("Can't get version to change to load ram patch err");
		return ret;
	}

	snprintf(filename, ATH3K_NAME_LEN, "ar3k/AthrBT_0x%08x.dfu",
		 le32_to_cpu(fw_version.rom_version));

	ret = request_firmware(&firmware, filename, &udev->dev);
	if (ret < 0) {
		BT_ERR("Patch file not found %s", filename);
		return ret;
	}

	pt_rom_version = get_unaligned_le32(firmware->data +
					    firmware->size - 8);
	pt_build_version = get_unaligned_le32(firmware->data +
					      firmware->size - 4);

	if (pt_rom_version != le32_to_cpu(fw_version.rom_version) ||
	    pt_build_version <= le32_to_cpu(fw_version.build_version)) {
		BT_ERR("Patch file version did not match with firmware");
		release_firmware(firmware);
		return -EINVAL;
	}

	ret = ath3k_load_fwfile(udev, firmware);
	release_firmware(firmware);

	return ret;
}