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
struct mwl8k_priv {int dummy; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct mwl8k_priv* priv; } ;

/* Variables and functions */
 int MAX_RESTART_ATTEMPTS ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mwl8k_hw_reset (struct mwl8k_priv*) ; 
 int mwl8k_load_firmware (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mwl8k_release_firmware (struct mwl8k_priv*) ; 
 int mwl8k_request_firmware (struct mwl8k_priv*,char*,int) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mwl8k_init_firmware(struct ieee80211_hw *hw, char *fw_image,
			       bool nowait)
{
	struct mwl8k_priv *priv = hw->priv;
	int rc;
	int count = MAX_RESTART_ATTEMPTS;

retry:
	/* Reset firmware and hardware */
	mwl8k_hw_reset(priv);

	/* Ask userland hotplug daemon for the device firmware */
	rc = mwl8k_request_firmware(priv, fw_image, nowait);
	if (rc) {
		wiphy_err(hw->wiphy, "Firmware files not found\n");
		return rc;
	}

	if (nowait)
		return rc;

	/* Load firmware into hardware */
	rc = mwl8k_load_firmware(hw);
	if (rc)
		wiphy_err(hw->wiphy, "Cannot start firmware\n");

	/* Reclaim memory once firmware is successfully loaded */
	mwl8k_release_firmware(priv);

	if (rc && count) {
		/* FW did not start successfully;
		 * lets try one more time
		 */
		count--;
		wiphy_err(hw->wiphy, "Trying to reload the firmware again\n");
		msleep(20);
		goto retry;
	}

	return rc;
}