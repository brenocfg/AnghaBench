#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iwl_priv {TYPE_2__* hw; scalar_t__ mac80211_registered; struct dentry* debugfs_dir; } ;
struct dentry {struct dentry* d_parent; } ;
struct TYPE_4__ {TYPE_1__* wiphy; } ;
struct TYPE_3__ {struct dentry* debugfsdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFS_ADD_FILE (int /*<<< orphan*/ ,struct dentry*,int) ; 
 int /*<<< orphan*/  bt_traffic ; 
 int /*<<< orphan*/  calib_disabled ; 
 int /*<<< orphan*/  chain_noise ; 
 int /*<<< orphan*/  channels ; 
 int /*<<< orphan*/  clear_ucode_statistics ; 
 int /*<<< orphan*/  current_sleep_command ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_symlink (char*,struct dentry*,char*) ; 
 int /*<<< orphan*/  disable_ht40 ; 
 int /*<<< orphan*/  echo_test ; 
 int /*<<< orphan*/  fw_restart ; 
 scalar_t__ iwl_advanced_bt_coexist (struct iwl_priv*) ; 
 int /*<<< orphan*/  log_event ; 
 int /*<<< orphan*/  missed_beacon ; 
 int /*<<< orphan*/  nvm ; 
 int /*<<< orphan*/  plcp_delta ; 
 int /*<<< orphan*/  power_save_status ; 
 int /*<<< orphan*/  protection_mode ; 
 int /*<<< orphan*/  qos ; 
 int /*<<< orphan*/  reply_tx_error ; 
 int /*<<< orphan*/  rf_reset ; 
 int /*<<< orphan*/  rx_handlers ; 
 int /*<<< orphan*/  rxon_filter_flags ; 
 int /*<<< orphan*/  rxon_flags ; 
 int /*<<< orphan*/  sensitivity ; 
 int /*<<< orphan*/  sleep_level_override ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,struct dentry*) ; 
 int /*<<< orphan*/  sram ; 
 int /*<<< orphan*/  stations ; 
 int /*<<< orphan*/  status ; 
 int /*<<< orphan*/  temperature ; 
 int /*<<< orphan*/  thermal_throttling ; 
 int /*<<< orphan*/  txfifo_flush ; 
 int /*<<< orphan*/  ucode_bt_stats ; 
 int /*<<< orphan*/  ucode_general_stats ; 
 int /*<<< orphan*/  ucode_rx_stats ; 
 int /*<<< orphan*/  ucode_tracing ; 
 int /*<<< orphan*/  ucode_tx_stats ; 
 int /*<<< orphan*/  wowlan_sram ; 

void iwl_dbgfs_register(struct iwl_priv *priv, struct dentry *dbgfs_dir)
{
	struct dentry *dir_data, *dir_rf, *dir_debug;

	priv->debugfs_dir = dbgfs_dir;

	dir_data = debugfs_create_dir("data", dbgfs_dir);
	dir_rf = debugfs_create_dir("rf", dbgfs_dir);
	dir_debug = debugfs_create_dir("debug", dbgfs_dir);

	DEBUGFS_ADD_FILE(nvm, dir_data, 0400);
	DEBUGFS_ADD_FILE(sram, dir_data, 0600);
	DEBUGFS_ADD_FILE(wowlan_sram, dir_data, 0400);
	DEBUGFS_ADD_FILE(stations, dir_data, 0400);
	DEBUGFS_ADD_FILE(channels, dir_data, 0400);
	DEBUGFS_ADD_FILE(status, dir_data, 0400);
	DEBUGFS_ADD_FILE(rx_handlers, dir_data, 0600);
	DEBUGFS_ADD_FILE(qos, dir_data, 0400);
	DEBUGFS_ADD_FILE(sleep_level_override, dir_data, 0600);
	DEBUGFS_ADD_FILE(current_sleep_command, dir_data, 0400);
	DEBUGFS_ADD_FILE(thermal_throttling, dir_data, 0400);
	DEBUGFS_ADD_FILE(disable_ht40, dir_data, 0600);
	DEBUGFS_ADD_FILE(temperature, dir_data, 0400);

	DEBUGFS_ADD_FILE(power_save_status, dir_debug, 0400);
	DEBUGFS_ADD_FILE(clear_ucode_statistics, dir_debug, 0200);
	DEBUGFS_ADD_FILE(missed_beacon, dir_debug, 0200);
	DEBUGFS_ADD_FILE(plcp_delta, dir_debug, 0600);
	DEBUGFS_ADD_FILE(rf_reset, dir_debug, 0600);
	DEBUGFS_ADD_FILE(ucode_rx_stats, dir_debug, 0400);
	DEBUGFS_ADD_FILE(ucode_tx_stats, dir_debug, 0400);
	DEBUGFS_ADD_FILE(ucode_general_stats, dir_debug, 0400);
	DEBUGFS_ADD_FILE(txfifo_flush, dir_debug, 0200);
	DEBUGFS_ADD_FILE(protection_mode, dir_debug, 0600);
	DEBUGFS_ADD_FILE(sensitivity, dir_debug, 0400);
	DEBUGFS_ADD_FILE(chain_noise, dir_debug, 0400);
	DEBUGFS_ADD_FILE(ucode_tracing, dir_debug, 0600);
	DEBUGFS_ADD_FILE(ucode_bt_stats, dir_debug, 0400);
	DEBUGFS_ADD_FILE(reply_tx_error, dir_debug, 0400);
	DEBUGFS_ADD_FILE(rxon_flags, dir_debug, 0200);
	DEBUGFS_ADD_FILE(rxon_filter_flags, dir_debug, 0200);
	DEBUGFS_ADD_FILE(echo_test, dir_debug, 0200);
	DEBUGFS_ADD_FILE(fw_restart, dir_debug, 0200);
#ifdef CONFIG_IWLWIFI_DEBUG
	DEBUGFS_ADD_FILE(log_event, dir_debug, 0600);
#endif

	if (iwl_advanced_bt_coexist(priv))
		DEBUGFS_ADD_FILE(bt_traffic, dir_debug, 0400);

	/* Calibrations disabled/enabled status*/
	DEBUGFS_ADD_FILE(calib_disabled, dir_rf, 0600);

	/*
	 * Create a symlink with mac80211. This is not very robust, as it does
	 * not remove the symlink created. The implicit assumption is that
	 * when the opmode exits, mac80211 will also exit, and will remove
	 * this symlink as part of its cleanup.
	 */
	if (priv->mac80211_registered) {
		char buf[100];
		struct dentry *mac80211_dir, *dev_dir;

		dev_dir = dbgfs_dir->d_parent;
		mac80211_dir = priv->hw->wiphy->debugfsdir;

		snprintf(buf, 100, "../../%pd2", dev_dir);

		debugfs_create_symlink("iwlwifi", mac80211_dir, buf);
	}
}