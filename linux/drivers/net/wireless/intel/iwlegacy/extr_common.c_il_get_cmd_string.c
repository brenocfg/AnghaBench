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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  C_ADD_STA ; 
 int /*<<< orphan*/  C_BT_CONFIG ; 
 int /*<<< orphan*/  C_CHANNEL_SWITCH ; 
 int /*<<< orphan*/  C_CT_KILL_CONFIG ; 
 int /*<<< orphan*/  C_LEDS ; 
 int /*<<< orphan*/  C_PHY_CALIBRATION ; 
 int /*<<< orphan*/  C_POWER_TBL ; 
 int /*<<< orphan*/  C_QOS_PARAM ; 
 int /*<<< orphan*/  C_RATE_SCALE ; 
 int /*<<< orphan*/  C_REM_STA ; 
 int /*<<< orphan*/  C_RXON ; 
 int /*<<< orphan*/  C_RXON_ASSOC ; 
 int /*<<< orphan*/  C_RXON_TIMING ; 
 int /*<<< orphan*/  C_SCAN ; 
 int /*<<< orphan*/  C_SCAN_ABORT ; 
 int /*<<< orphan*/  C_SENSITIVITY ; 
 int /*<<< orphan*/  C_SPECTRUM_MEASUREMENT ; 
 int /*<<< orphan*/  C_STATS ; 
 int /*<<< orphan*/  C_TX ; 
 int /*<<< orphan*/  C_TX_BEACON ; 
 int /*<<< orphan*/  C_TX_LINK_QUALITY_CMD ; 
 int /*<<< orphan*/  C_TX_PWR_TBL ; 
 int /*<<< orphan*/  C_WEPKEY ; 
 int /*<<< orphan*/  IL_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  N_3945_RX ; 
 int /*<<< orphan*/  N_ALIVE ; 
 int /*<<< orphan*/  N_BEACON ; 
 int /*<<< orphan*/  N_CARD_STATE ; 
 int /*<<< orphan*/  N_CHANNEL_SWITCH ; 
 int /*<<< orphan*/  N_COMPRESSED_BA ; 
 int /*<<< orphan*/  N_ERROR ; 
 int /*<<< orphan*/  N_MISSED_BEACONS ; 
 int /*<<< orphan*/  N_PM_DEBUG_STATS ; 
 int /*<<< orphan*/  N_PM_SLEEP ; 
 int /*<<< orphan*/  N_RX ; 
 int /*<<< orphan*/  N_RX_MPDU ; 
 int /*<<< orphan*/  N_RX_PHY ; 
 int /*<<< orphan*/  N_SCAN_COMPLETE ; 
 int /*<<< orphan*/  N_SCAN_RESULTS ; 
 int /*<<< orphan*/  N_SCAN_START ; 
 int /*<<< orphan*/  N_SPECTRUM_MEASUREMENT ; 
 int /*<<< orphan*/  N_STATS ; 

const char *
il_get_cmd_string(u8 cmd)
{
	switch (cmd) {
		IL_CMD(N_ALIVE);
		IL_CMD(N_ERROR);
		IL_CMD(C_RXON);
		IL_CMD(C_RXON_ASSOC);
		IL_CMD(C_QOS_PARAM);
		IL_CMD(C_RXON_TIMING);
		IL_CMD(C_ADD_STA);
		IL_CMD(C_REM_STA);
		IL_CMD(C_WEPKEY);
		IL_CMD(N_3945_RX);
		IL_CMD(C_TX);
		IL_CMD(C_RATE_SCALE);
		IL_CMD(C_LEDS);
		IL_CMD(C_TX_LINK_QUALITY_CMD);
		IL_CMD(C_CHANNEL_SWITCH);
		IL_CMD(N_CHANNEL_SWITCH);
		IL_CMD(C_SPECTRUM_MEASUREMENT);
		IL_CMD(N_SPECTRUM_MEASUREMENT);
		IL_CMD(C_POWER_TBL);
		IL_CMD(N_PM_SLEEP);
		IL_CMD(N_PM_DEBUG_STATS);
		IL_CMD(C_SCAN);
		IL_CMD(C_SCAN_ABORT);
		IL_CMD(N_SCAN_START);
		IL_CMD(N_SCAN_RESULTS);
		IL_CMD(N_SCAN_COMPLETE);
		IL_CMD(N_BEACON);
		IL_CMD(C_TX_BEACON);
		IL_CMD(C_TX_PWR_TBL);
		IL_CMD(C_BT_CONFIG);
		IL_CMD(C_STATS);
		IL_CMD(N_STATS);
		IL_CMD(N_CARD_STATE);
		IL_CMD(N_MISSED_BEACONS);
		IL_CMD(C_CT_KILL_CONFIG);
		IL_CMD(C_SENSITIVITY);
		IL_CMD(C_PHY_CALIBRATION);
		IL_CMD(N_RX_PHY);
		IL_CMD(N_RX_MPDU);
		IL_CMD(N_RX);
		IL_CMD(N_COMPRESSED_BA);
	default:
		return "UNKNOWN";

	}
}