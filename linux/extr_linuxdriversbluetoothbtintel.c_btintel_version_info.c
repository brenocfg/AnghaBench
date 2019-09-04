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
struct intel_version {int fw_variant; int fw_revision; scalar_t__ fw_build_yy; int /*<<< orphan*/  fw_build_ww; int /*<<< orphan*/  fw_build_num; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt_dev_info (struct hci_dev*,char*,char const*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void btintel_version_info(struct hci_dev *hdev, struct intel_version *ver)
{
	const char *variant;

	switch (ver->fw_variant) {
	case 0x06:
		variant = "Bootloader";
		break;
	case 0x23:
		variant = "Firmware";
		break;
	default:
		return;
	}

	bt_dev_info(hdev, "%s revision %u.%u build %u week %u %u",
		    variant, ver->fw_revision >> 4, ver->fw_revision & 0x0f,
		    ver->fw_build_num, ver->fw_build_ww,
		    2000 + ver->fw_build_yy);
}