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
struct wmi_fw_version {int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct ieee80211_hw {TYPE_1__* wiphy; } ;
struct ath9k_htc_priv {int fw_version_major; int fw_version_minor; int /*<<< orphan*/  fw_flags; int /*<<< orphan*/  dev; struct ieee80211_hw* hw; } ;
typedef  int /*<<< orphan*/  cmd_rsp ;
struct TYPE_2__ {int /*<<< orphan*/  fw_version; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HTC_FWFLAG_NO_RMW ; 
 int MAJOR_VERSION_REQ ; 
 int MINOR_VERSION_REQ ; 
 int /*<<< orphan*/  WMI_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WMI_GET_FW_VERSION ; 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (struct wmi_fw_version*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath9k_init_firmware_version(struct ath9k_htc_priv *priv)
{
	struct ieee80211_hw *hw = priv->hw;
	struct wmi_fw_version cmd_rsp;
	int ret;

	memset(&cmd_rsp, 0, sizeof(cmd_rsp));

	WMI_CMD(WMI_GET_FW_VERSION);
	if (ret)
		return -EINVAL;

	priv->fw_version_major = be16_to_cpu(cmd_rsp.major);
	priv->fw_version_minor = be16_to_cpu(cmd_rsp.minor);

	snprintf(hw->wiphy->fw_version, sizeof(hw->wiphy->fw_version), "%d.%d",
		 priv->fw_version_major,
		 priv->fw_version_minor);

	dev_info(priv->dev, "ath9k_htc: FW Version: %d.%d\n",
		 priv->fw_version_major,
		 priv->fw_version_minor);

	/*
	 * Check if the available FW matches the driver's
	 * required version.
	 */
	if (priv->fw_version_major != MAJOR_VERSION_REQ ||
	    priv->fw_version_minor < MINOR_VERSION_REQ) {
		dev_err(priv->dev, "ath9k_htc: Please upgrade to FW version %d.%d\n",
			MAJOR_VERSION_REQ, MINOR_VERSION_REQ);
		return -EINVAL;
	}

	if (priv->fw_version_major == 1 && priv->fw_version_minor < 4)
		set_bit(HTC_FWFLAG_NO_RMW, &priv->fw_flags);

	dev_info(priv->dev, "FW RMW support: %s\n",
		test_bit(HTC_FWFLAG_NO_RMW, &priv->fw_flags) ? "Off" : "On");

	return 0;
}