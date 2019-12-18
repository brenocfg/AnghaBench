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
struct ieee80211_hw {int dummy; } ;
struct fw_priv {int /*<<< orphan*/  rf_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtl92s_firmware_header_map_rftype (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl92s_firmwareheader_priveupdate(struct ieee80211_hw *hw,
		struct fw_priv *pfw_priv)
{
	/* Update RF types for RATR settings. */
	pfw_priv->rf_config = _rtl92s_firmware_header_map_rftype(hw);
}