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
struct rtl_fw {int /*<<< orphan*/  fw_name; int /*<<< orphan*/  dev; int /*<<< orphan*/  fw; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 
 int request_firmware (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_fw_data_ok (struct rtl_fw*) ; 
 int /*<<< orphan*/  rtl_fw_format_ok (struct rtl_fw*) ; 

int rtl_fw_request_firmware(struct rtl_fw *rtl_fw)
{
	int rc;

	rc = request_firmware(&rtl_fw->fw, rtl_fw->fw_name, rtl_fw->dev);
	if (rc < 0)
		goto out;

	if (!rtl_fw_format_ok(rtl_fw) || !rtl_fw_data_ok(rtl_fw)) {
		release_firmware(rtl_fw->fw);
		rc = -EINVAL;
		goto out;
	}

	return 0;
out:
	dev_err(rtl_fw->dev, "Unable to load firmware %s (%d)\n",
		rtl_fw->fw_name, rc);
	return rc;
}