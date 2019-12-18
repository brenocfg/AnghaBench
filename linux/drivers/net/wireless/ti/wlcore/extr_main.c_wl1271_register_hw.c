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
typedef  int u8 ;
typedef  int u32 ;
struct wlcore_platdev_data {TYPE_1__* family; } ;
struct wl1271 {int mac80211_registered; int nvs_len; int fuse_oui_addr; int fuse_nic_addr; int /*<<< orphan*/  hw; scalar_t__ nvs; struct platform_device* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int WLCORE_TI_OUI_ADDRESS ; 
 struct wlcore_platdev_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int get_random_int () ; 
 int ieee80211_register_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_debugfs_init (struct wl1271*) ; 
 int /*<<< orphan*/  wl1271_error (char*,int) ; 
 int /*<<< orphan*/  wl1271_notice (char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*) ; 
 int /*<<< orphan*/  wl12xx_derive_mac_addresses (struct wl1271*,int,int) ; 

__attribute__((used)) static int wl1271_register_hw(struct wl1271 *wl)
{
	int ret;
	u32 oui_addr = 0, nic_addr = 0;
	struct platform_device *pdev = wl->pdev;
	struct wlcore_platdev_data *pdev_data = dev_get_platdata(&pdev->dev);

	if (wl->mac80211_registered)
		return 0;

	if (wl->nvs_len >= 12) {
		/* NOTE: The wl->nvs->nvs element must be first, in
		 * order to simplify the casting, we assume it is at
		 * the beginning of the wl->nvs structure.
		 */
		u8 *nvs_ptr = (u8 *)wl->nvs;

		oui_addr =
			(nvs_ptr[11] << 16) + (nvs_ptr[10] << 8) + nvs_ptr[6];
		nic_addr =
			(nvs_ptr[5] << 16) + (nvs_ptr[4] << 8) + nvs_ptr[3];
	}

	/* if the MAC address is zeroed in the NVS derive from fuse */
	if (oui_addr == 0 && nic_addr == 0) {
		oui_addr = wl->fuse_oui_addr;
		/* fuse has the BD_ADDR, the WLAN addresses are the next two */
		nic_addr = wl->fuse_nic_addr + 1;
	}

	if (oui_addr == 0xdeadbe && nic_addr == 0xef0000) {
		wl1271_warning("Detected unconfigured mac address in nvs, derive from fuse instead.");
		if (!strcmp(pdev_data->family->name, "wl18xx")) {
			wl1271_warning("This default nvs file can be removed from the file system");
		} else {
			wl1271_warning("Your device performance is not optimized.");
			wl1271_warning("Please use the calibrator tool to configure your device.");
		}

		if (wl->fuse_oui_addr == 0 && wl->fuse_nic_addr == 0) {
			wl1271_warning("Fuse mac address is zero. using random mac");
			/* Use TI oui and a random nic */
			oui_addr = WLCORE_TI_OUI_ADDRESS;
			nic_addr = get_random_int();
		} else {
			oui_addr = wl->fuse_oui_addr;
			/* fuse has the BD_ADDR, the WLAN addresses are the next two */
			nic_addr = wl->fuse_nic_addr + 1;
		}
	}

	wl12xx_derive_mac_addresses(wl, oui_addr, nic_addr);

	ret = ieee80211_register_hw(wl->hw);
	if (ret < 0) {
		wl1271_error("unable to register mac80211 hw: %d", ret);
		goto out;
	}

	wl->mac80211_registered = true;

	wl1271_debugfs_init(wl);

	wl1271_notice("loaded");

out:
	return ret;
}