#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct iwl_scan_config_v2 {int dummy; } ;
struct iwl_scan_config_v1 {int dummy; } ;
struct iwl_mvm {int scan_type; int hb_scan_type; TYPE_4__* fw; TYPE_2__* nvm_data; } ;
struct iwl_host_cmd {int* len; int /*<<< orphan*/ * dataflags; void** data; int /*<<< orphan*/  id; } ;
typedef  enum iwl_mvm_scan_type { ____Placeholder_iwl_mvm_scan_type } iwl_mvm_scan_type ;
struct TYPE_7__ {int n_scan_channels; } ;
struct TYPE_8__ {TYPE_3__ ucode_capa; } ;
struct TYPE_6__ {TYPE_1__* bands; } ;
struct TYPE_5__ {int n_channels; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IWL_ALWAYS_LONG_GROUP ; 
 int IWL_CHANNEL_FLAG_ACCURATE_EBS ; 
 int IWL_CHANNEL_FLAG_EBS ; 
 int IWL_CHANNEL_FLAG_EBS_ADD ; 
 int IWL_CHANNEL_FLAG_PRE_SCAN_PASSIVE2ACTIVE ; 
 int /*<<< orphan*/  IWL_DEBUG_SCAN (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_HCMD_DFL_NOCOPY ; 
 int IWL_SCAN_TYPE_NOT_SET ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  SCAN_CFG_CMD ; 
 int SCAN_CONFIG_FLAG_ACTIVATE ; 
 int SCAN_CONFIG_FLAG_ALLOW_CHUB_REQS ; 
 int SCAN_CONFIG_FLAG_CLEAR_FRAGMENTED ; 
 int SCAN_CONFIG_FLAG_CLEAR_LMAC2_FRAGMENTED ; 
 int SCAN_CONFIG_FLAG_SET_ALL_TIMES ; 
 int SCAN_CONFIG_FLAG_SET_AUX_STA_ID ; 
 int SCAN_CONFIG_FLAG_SET_CHANNEL_FLAGS ; 
 int SCAN_CONFIG_FLAG_SET_FRAGMENTED ; 
 int SCAN_CONFIG_FLAG_SET_LEGACY_RATES ; 
 int SCAN_CONFIG_FLAG_SET_LMAC2_FRAGMENTED ; 
 int SCAN_CONFIG_FLAG_SET_MAC_ADDR ; 
 int SCAN_CONFIG_FLAG_SET_RX_CHAINS ; 
 int SCAN_CONFIG_FLAG_SET_TX_CHAINS ; 
 int SCAN_CONFIG_N_CHANNELS (int) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  iwl_cmd_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_cdb_scan_api (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_fill_scan_config_v1 (struct iwl_mvm*,void*,int,int,int) ; 
 int /*<<< orphan*/  iwl_mvm_fill_scan_config_v2 (struct iwl_mvm*,void*,int,int,int) ; 
 int iwl_mvm_get_scan_type (struct iwl_mvm*,int /*<<< orphan*/ *) ; 
 int iwl_mvm_get_scan_type_band (struct iwl_mvm*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ iwl_mvm_is_cdb_supported (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_is_scan_fragmented (int) ; 
 int iwl_mvm_send_cmd (struct iwl_mvm*,struct iwl_host_cmd*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_mvm_legacy_config_scan(struct iwl_mvm *mvm)
{
	void *cfg;
	int ret, cmd_size;
	struct iwl_host_cmd cmd = {
		.id = iwl_cmd_id(SCAN_CFG_CMD, IWL_ALWAYS_LONG_GROUP, 0),
	};
	enum iwl_mvm_scan_type type;
	enum iwl_mvm_scan_type hb_type = IWL_SCAN_TYPE_NOT_SET;
	int num_channels =
		mvm->nvm_data->bands[NL80211_BAND_2GHZ].n_channels +
		mvm->nvm_data->bands[NL80211_BAND_5GHZ].n_channels;
	u32 flags;
	u8 channel_flags;

	if (WARN_ON(num_channels > mvm->fw->ucode_capa.n_scan_channels))
		num_channels = mvm->fw->ucode_capa.n_scan_channels;

	if (iwl_mvm_is_cdb_supported(mvm)) {
		type = iwl_mvm_get_scan_type_band(mvm, NULL,
						  NL80211_BAND_2GHZ);
		hb_type = iwl_mvm_get_scan_type_band(mvm, NULL,
						     NL80211_BAND_5GHZ);
		if (type == mvm->scan_type && hb_type == mvm->hb_scan_type)
			return 0;
	} else {
		type = iwl_mvm_get_scan_type(mvm, NULL);
		if (type == mvm->scan_type)
			return 0;
	}

	if (iwl_mvm_cdb_scan_api(mvm))
		cmd_size = sizeof(struct iwl_scan_config_v2);
	else
		cmd_size = sizeof(struct iwl_scan_config_v1);
	cmd_size += num_channels;

	cfg = kzalloc(cmd_size, GFP_KERNEL);
	if (!cfg)
		return -ENOMEM;

	flags = SCAN_CONFIG_FLAG_ACTIVATE |
		 SCAN_CONFIG_FLAG_ALLOW_CHUB_REQS |
		 SCAN_CONFIG_FLAG_SET_TX_CHAINS |
		 SCAN_CONFIG_FLAG_SET_RX_CHAINS |
		 SCAN_CONFIG_FLAG_SET_AUX_STA_ID |
		 SCAN_CONFIG_FLAG_SET_ALL_TIMES |
		 SCAN_CONFIG_FLAG_SET_LEGACY_RATES |
		 SCAN_CONFIG_FLAG_SET_MAC_ADDR |
		 SCAN_CONFIG_FLAG_SET_CHANNEL_FLAGS |
		 SCAN_CONFIG_N_CHANNELS(num_channels) |
		 (iwl_mvm_is_scan_fragmented(type) ?
		  SCAN_CONFIG_FLAG_SET_FRAGMENTED :
		  SCAN_CONFIG_FLAG_CLEAR_FRAGMENTED);

	channel_flags = IWL_CHANNEL_FLAG_EBS |
			IWL_CHANNEL_FLAG_ACCURATE_EBS |
			IWL_CHANNEL_FLAG_EBS_ADD |
			IWL_CHANNEL_FLAG_PRE_SCAN_PASSIVE2ACTIVE;

	/*
	 * Check for fragmented scan on LMAC2 - high band.
	 * LMAC1 - low band is checked above.
	 */
	if (iwl_mvm_cdb_scan_api(mvm)) {
		if (iwl_mvm_is_cdb_supported(mvm))
			flags |= (iwl_mvm_is_scan_fragmented(hb_type)) ?
				 SCAN_CONFIG_FLAG_SET_LMAC2_FRAGMENTED :
				 SCAN_CONFIG_FLAG_CLEAR_LMAC2_FRAGMENTED;
		iwl_mvm_fill_scan_config_v2(mvm, cfg, flags, channel_flags,
					    num_channels);
	} else {
		iwl_mvm_fill_scan_config_v1(mvm, cfg, flags, channel_flags,
					    num_channels);
	}

	cmd.data[0] = cfg;
	cmd.len[0] = cmd_size;
	cmd.dataflags[0] = IWL_HCMD_DFL_NOCOPY;

	IWL_DEBUG_SCAN(mvm, "Sending UMAC scan config\n");

	ret = iwl_mvm_send_cmd(mvm, &cmd);
	if (!ret) {
		mvm->scan_type = type;
		mvm->hb_scan_type = hb_type;
	}

	kfree(cfg);
	return ret;
}