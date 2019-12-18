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
struct wl18xx_static_data_priv {int /*<<< orphan*/  phy_version; } ;
struct wl1271_static_data {scalar_t__ priv; } ;
struct TYPE_2__ {char* phy_fw_ver_str; } ;
struct wl1271 {TYPE_1__ chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wl1271_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wl18xx_handle_static_data(struct wl1271 *wl,
				     struct wl1271_static_data *static_data)
{
	struct wl18xx_static_data_priv *static_data_priv =
		(struct wl18xx_static_data_priv *) static_data->priv;

	strncpy(wl->chip.phy_fw_ver_str, static_data_priv->phy_version,
		sizeof(wl->chip.phy_fw_ver_str));

	/* make sure the string is NULL-terminated */
	wl->chip.phy_fw_ver_str[sizeof(wl->chip.phy_fw_ver_str) - 1] = '\0';

	wl1271_info("PHY firmware version: %s", static_data_priv->phy_version);

	return 0;
}