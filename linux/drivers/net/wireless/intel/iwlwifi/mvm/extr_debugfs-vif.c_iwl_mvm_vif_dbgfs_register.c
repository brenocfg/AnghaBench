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
struct iwl_mvm_vif {int /*<<< orphan*/  dbgfs_slink; int /*<<< orphan*/  dbgfs_dir; } ;
struct iwl_mvm {int /*<<< orphan*/  debugfs_dir; struct iwl_mvm_vif* bf_allowed_vif; } ;
struct ieee80211_vif {scalar_t__ type; scalar_t__ p2p; struct dentry* debugfs_dir; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;
struct TYPE_4__ {scalar_t__ power_scheme; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,struct dentry*) ; 
 scalar_t__ IWL_POWER_SCHEME_CAM ; 
 int /*<<< orphan*/  MVM_DEBUGFS_ADD_FILE_VIF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  bf_params ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_symlink (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 TYPE_2__ iwlmvm_mod_params ; 
 int /*<<< orphan*/  low_latency ; 
 int /*<<< orphan*/  low_latency_force ; 
 int /*<<< orphan*/  mac_params ; 
 int /*<<< orphan*/  os_device_timediff ; 
 int /*<<< orphan*/  pm_params ; 
 int /*<<< orphan*/  quota_min ; 
 int /*<<< orphan*/  rx_phyinfo ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_pwr_lmt ; 
 int /*<<< orphan*/  uapsd_misbehaving ; 

void iwl_mvm_vif_dbgfs_register(struct iwl_mvm *mvm, struct ieee80211_vif *vif)
{
	struct dentry *dbgfs_dir = vif->debugfs_dir;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	char buf[100];

	/*
	 * Check if debugfs directory already exist before creating it.
	 * This may happen when, for example, resetting hw or suspend-resume
	 */
	if (!dbgfs_dir || mvmvif->dbgfs_dir)
		return;

	mvmvif->dbgfs_dir = debugfs_create_dir("iwlmvm", dbgfs_dir);
	if (IS_ERR_OR_NULL(mvmvif->dbgfs_dir)) {
		IWL_ERR(mvm, "Failed to create debugfs directory under %pd\n",
			dbgfs_dir);
		return;
	}

	if (iwlmvm_mod_params.power_scheme != IWL_POWER_SCHEME_CAM &&
	    ((vif->type == NL80211_IFTYPE_STATION && !vif->p2p) ||
	     (vif->type == NL80211_IFTYPE_STATION && vif->p2p)))
		MVM_DEBUGFS_ADD_FILE_VIF(pm_params, mvmvif->dbgfs_dir, 0600);

	MVM_DEBUGFS_ADD_FILE_VIF(tx_pwr_lmt, mvmvif->dbgfs_dir, 0400);
	MVM_DEBUGFS_ADD_FILE_VIF(mac_params, mvmvif->dbgfs_dir, 0400);
	MVM_DEBUGFS_ADD_FILE_VIF(low_latency, mvmvif->dbgfs_dir, 0600);
	MVM_DEBUGFS_ADD_FILE_VIF(low_latency_force, mvmvif->dbgfs_dir, 0600);
	MVM_DEBUGFS_ADD_FILE_VIF(uapsd_misbehaving, mvmvif->dbgfs_dir, 0600);
	MVM_DEBUGFS_ADD_FILE_VIF(rx_phyinfo, mvmvif->dbgfs_dir, 0600);
	MVM_DEBUGFS_ADD_FILE_VIF(quota_min, mvmvif->dbgfs_dir, 0600);
	MVM_DEBUGFS_ADD_FILE_VIF(os_device_timediff, mvmvif->dbgfs_dir, 0400);

	if (vif->type == NL80211_IFTYPE_STATION && !vif->p2p &&
	    mvmvif == mvm->bf_allowed_vif)
		MVM_DEBUGFS_ADD_FILE_VIF(bf_params, mvmvif->dbgfs_dir, 0600);

	/*
	 * Create symlink for convenience pointing to interface specific
	 * debugfs entries for the driver. For example, under
	 * /sys/kernel/debug/iwlwifi/0000\:02\:00.0/iwlmvm/
	 * find
	 * netdev:wlan0 -> ../../../ieee80211/phy0/netdev:wlan0/iwlmvm/
	 */
	snprintf(buf, 100, "../../../%pd3/%pd",
		 dbgfs_dir,
		 mvmvif->dbgfs_dir);

	mvmvif->dbgfs_slink = debugfs_create_symlink(dbgfs_dir->d_name.name,
						     mvm->debugfs_dir, buf);
}