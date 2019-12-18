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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_nvm_data {int /*<<< orphan*/  valid_rx_ant; int /*<<< orphan*/  valid_tx_ant; int /*<<< orphan*/  radio_cfg_pnum; int /*<<< orphan*/  radio_cfg_dash; int /*<<< orphan*/  radio_cfg_step; int /*<<< orphan*/  radio_cfg_type; } ;
struct iwl_cfg {scalar_t__ nvm_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT_NVM_RF_CFG_DASH_MSK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT_NVM_RF_CFG_FLAVOR_MSK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT_NVM_RF_CFG_RX_ANT_MSK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT_NVM_RF_CFG_STEP_MSK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT_NVM_RF_CFG_TX_ANT_MSK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT_NVM_RF_CFG_TYPE_MSK (int /*<<< orphan*/ ) ; 
 scalar_t__ IWL_NVM_EXT ; 
 int /*<<< orphan*/  NVM_RF_CFG_DASH_MSK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVM_RF_CFG_PNUM_MSK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVM_RF_CFG_STEP_MSK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVM_RF_CFG_TYPE_MSK (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_set_radio_cfg(const struct iwl_cfg *cfg,
			      struct iwl_nvm_data *data,
			      u32 radio_cfg)
{
	if (cfg->nvm_type != IWL_NVM_EXT) {
		data->radio_cfg_type = NVM_RF_CFG_TYPE_MSK(radio_cfg);
		data->radio_cfg_step = NVM_RF_CFG_STEP_MSK(radio_cfg);
		data->radio_cfg_dash = NVM_RF_CFG_DASH_MSK(radio_cfg);
		data->radio_cfg_pnum = NVM_RF_CFG_PNUM_MSK(radio_cfg);
		return;
	}

	/* set the radio configuration for family 8000 */
	data->radio_cfg_type = EXT_NVM_RF_CFG_TYPE_MSK(radio_cfg);
	data->radio_cfg_step = EXT_NVM_RF_CFG_STEP_MSK(radio_cfg);
	data->radio_cfg_dash = EXT_NVM_RF_CFG_DASH_MSK(radio_cfg);
	data->radio_cfg_pnum = EXT_NVM_RF_CFG_FLAVOR_MSK(radio_cfg);
	data->valid_tx_ant = EXT_NVM_RF_CFG_TX_ANT_MSK(radio_cfg);
	data->valid_rx_ant = EXT_NVM_RF_CFG_RX_ANT_MSK(radio_cfg);
}