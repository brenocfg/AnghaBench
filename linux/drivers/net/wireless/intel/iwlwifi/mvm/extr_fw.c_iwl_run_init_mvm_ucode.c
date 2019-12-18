#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct iwl_nvm_data {int dummy; } ;
struct iwl_notification_wait {int dummy; } ;
struct iwl_mvm {int rfkill_safe_init_done; TYPE_6__* nvm_data; int /*<<< orphan*/  notif_wait; TYPE_3__* trans; scalar_t__ nvm_file_name; int /*<<< orphan*/  phy_db; int /*<<< orphan*/  mutex; } ;
struct ieee80211_rate {int dummy; } ;
struct ieee80211_channel {int dummy; } ;
struct TYPE_14__ {scalar_t__ init_dbg; } ;
struct TYPE_13__ {scalar_t__ nvm_version; TYPE_5__* bands; scalar_t__ channels; } ;
struct TYPE_12__ {int n_channels; int n_bitrates; TYPE_4__* bitrates; scalar_t__ channels; } ;
struct TYPE_11__ {int hw_value; } ;
struct TYPE_10__ {TYPE_2__* cfg; TYPE_1__* trans_cfg; } ;
struct TYPE_9__ {scalar_t__ nvm_ver; } ;
struct TYPE_8__ {scalar_t__ device_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
#define  CALIB_RES_NOTIF_PHY_DB 129 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  INIT_COMPLETE_NOTIF 128 
 int /*<<< orphan*/  IWL_DEBUG_RF_KILL (struct iwl_mvm*,char*) ; 
 scalar_t__ IWL_DEVICE_FAMILY_8000 ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  IWL_UCODE_INIT ; 
 int /*<<< orphan*/  MVM_UCODE_CALIB_TIMEOUT ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  iwl_init_notification_wait (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_get_valid_tx_ant (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_has_unified_ucode (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_is_radio_hw_killed (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_load_nvm_to_nic (struct iwl_mvm*) ; 
 int iwl_mvm_load_ucode_wait_alive (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int iwl_mvm_send_bt_init_conf (struct iwl_mvm*) ; 
 int iwl_nvm_init (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_remove_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*) ; 
 int iwl_run_unified_mvm_ucode (struct iwl_mvm*,int) ; 
 int iwl_send_phy_cfg_cmd (struct iwl_mvm*) ; 
 int iwl_send_tx_ant_cfg (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int iwl_wait_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_wait_phy_db_entry ; 
 TYPE_7__ iwlmvm_mod_params ; 
 TYPE_6__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_run_init_mvm_ucode(struct iwl_mvm *mvm, bool read_nvm)
{
	struct iwl_notification_wait calib_wait;
	static const u16 init_complete[] = {
		INIT_COMPLETE_NOTIF,
		CALIB_RES_NOTIF_PHY_DB
	};
	int ret;

	if (iwl_mvm_has_unified_ucode(mvm))
		return iwl_run_unified_mvm_ucode(mvm, true);

	lockdep_assert_held(&mvm->mutex);

	mvm->rfkill_safe_init_done = false;

	iwl_init_notification_wait(&mvm->notif_wait,
				   &calib_wait,
				   init_complete,
				   ARRAY_SIZE(init_complete),
				   iwl_wait_phy_db_entry,
				   mvm->phy_db);

	/* Will also start the device */
	ret = iwl_mvm_load_ucode_wait_alive(mvm, IWL_UCODE_INIT);
	if (ret) {
		IWL_ERR(mvm, "Failed to start INIT ucode: %d\n", ret);
		goto remove_notif;
	}

	if (mvm->trans->trans_cfg->device_family < IWL_DEVICE_FAMILY_8000) {
		ret = iwl_mvm_send_bt_init_conf(mvm);
		if (ret)
			goto remove_notif;
	}

	/* Read the NVM only at driver load time, no need to do this twice */
	if (read_nvm) {
		ret = iwl_nvm_init(mvm);
		if (ret) {
			IWL_ERR(mvm, "Failed to read NVM: %d\n", ret);
			goto remove_notif;
		}
	}

	/* In case we read the NVM from external file, load it to the NIC */
	if (mvm->nvm_file_name)
		iwl_mvm_load_nvm_to_nic(mvm);

	WARN_ONCE(mvm->nvm_data->nvm_version < mvm->trans->cfg->nvm_ver,
		  "Too old NVM version (0x%0x, required = 0x%0x)",
		  mvm->nvm_data->nvm_version, mvm->trans->cfg->nvm_ver);

	/*
	 * abort after reading the nvm in case RF Kill is on, we will complete
	 * the init seq later when RF kill will switch to off
	 */
	if (iwl_mvm_is_radio_hw_killed(mvm)) {
		IWL_DEBUG_RF_KILL(mvm,
				  "jump over all phy activities due to RF kill\n");
		goto remove_notif;
	}

	mvm->rfkill_safe_init_done = true;

	/* Send TX valid antennas before triggering calibrations */
	ret = iwl_send_tx_ant_cfg(mvm, iwl_mvm_get_valid_tx_ant(mvm));
	if (ret)
		goto remove_notif;

	ret = iwl_send_phy_cfg_cmd(mvm);
	if (ret) {
		IWL_ERR(mvm, "Failed to run INIT calibrations: %d\n",
			ret);
		goto remove_notif;
	}

	/*
	 * Some things may run in the background now, but we
	 * just wait for the calibration complete notification.
	 */
	ret = iwl_wait_notification(&mvm->notif_wait, &calib_wait,
				    MVM_UCODE_CALIB_TIMEOUT);
	if (!ret)
		goto out;

	if (iwl_mvm_is_radio_hw_killed(mvm)) {
		IWL_DEBUG_RF_KILL(mvm, "RFKILL while calibrating.\n");
		ret = 0;
	} else {
		IWL_ERR(mvm, "Failed to run INIT calibrations: %d\n",
			ret);
	}

	goto out;

remove_notif:
	iwl_remove_notification(&mvm->notif_wait, &calib_wait);
out:
	mvm->rfkill_safe_init_done = false;
	if (iwlmvm_mod_params.init_dbg && !mvm->nvm_data) {
		/* we want to debug INIT and we have no NVM - fake */
		mvm->nvm_data = kzalloc(sizeof(struct iwl_nvm_data) +
					sizeof(struct ieee80211_channel) +
					sizeof(struct ieee80211_rate),
					GFP_KERNEL);
		if (!mvm->nvm_data)
			return -ENOMEM;
		mvm->nvm_data->bands[0].channels = mvm->nvm_data->channels;
		mvm->nvm_data->bands[0].n_channels = 1;
		mvm->nvm_data->bands[0].n_bitrates = 1;
		mvm->nvm_data->bands[0].bitrates =
			(void *)mvm->nvm_data->channels + 1;
		mvm->nvm_data->bands[0].bitrates->hw_value = 10;
	}

	return ret;
}