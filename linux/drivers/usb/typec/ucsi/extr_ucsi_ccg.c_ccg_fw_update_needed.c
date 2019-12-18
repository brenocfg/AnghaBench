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
typedef  int /*<<< orphan*/  version ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  build; } ;
struct version_info {int /*<<< orphan*/  app; TYPE_1__ base; } ;
struct ucsi_ccg {int /*<<< orphan*/  info; struct device* dev; } ;
struct device {int dummy; } ;
typedef  enum enum_flash_mode { ____Placeholder_enum_flash_mode } enum_flash_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CCGX_RAB_DEVICE_MODE ; 
 int /*<<< orphan*/  CCGX_RAB_READ_ALL_VER ; 
 int FLASH_NOT_NEEDED ; 
 size_t FW1 ; 
 size_t FW2 ; 
 size_t PRIMARY ; 
 int SECONDARY ; 
 int SECONDARY_BL ; 
 scalar_t__ ccg_check_fw_version (struct ucsi_ccg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ccg_fw_names ; 
 int ccg_read (struct ucsi_ccg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (struct version_info*,char*,int) ; 
 scalar_t__ secondary_fw_min_ver ; 

__attribute__((used)) static int ccg_fw_update_needed(struct ucsi_ccg *uc,
				enum enum_flash_mode *mode)
{
	struct device *dev = uc->dev;
	int err;
	struct version_info version[3];

	err = ccg_read(uc, CCGX_RAB_DEVICE_MODE, (u8 *)(&uc->info),
		       sizeof(uc->info));
	if (err) {
		dev_err(dev, "read device mode failed\n");
		return err;
	}

	err = ccg_read(uc, CCGX_RAB_READ_ALL_VER, (u8 *)version,
		       sizeof(version));
	if (err) {
		dev_err(dev, "read device mode failed\n");
		return err;
	}

	if (memcmp(&version[FW1], "\0\0\0\0\0\0\0\0",
		   sizeof(struct version_info)) == 0) {
		dev_info(dev, "secondary fw is not flashed\n");
		*mode = SECONDARY_BL;
	} else if (le16_to_cpu(version[FW1].base.build) <
		secondary_fw_min_ver) {
		dev_info(dev, "secondary fw version is too low (< %d)\n",
			 secondary_fw_min_ver);
		*mode = SECONDARY;
	} else if (memcmp(&version[FW2], "\0\0\0\0\0\0\0\0",
		   sizeof(struct version_info)) == 0) {
		dev_info(dev, "primary fw is not flashed\n");
		*mode = PRIMARY;
	} else if (ccg_check_fw_version(uc, ccg_fw_names[PRIMARY],
		   &version[FW2].app)) {
		dev_info(dev, "found primary fw with later version\n");
		*mode = PRIMARY;
	} else {
		dev_info(dev, "secondary and primary fw are the latest\n");
		*mode = FLASH_NOT_NEEDED;
	}
	return 0;
}