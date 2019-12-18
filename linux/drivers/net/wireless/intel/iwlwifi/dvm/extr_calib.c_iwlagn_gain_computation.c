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
typedef  scalar_t__ u32 ;
struct iwl_chain_noise_data {int* delta_gain_code; int radio_write; int /*<<< orphan*/  state; scalar_t__* disconn_array; } ;
struct iwl_priv {int /*<<< orphan*/  phy_calib_chain_noise_gain_cmd; TYPE_1__* lib; struct iwl_chain_noise_data chain_noise_data; } ;
struct iwl_calib_chain_noise_gain_cmd {int delta_gain_1; int delta_gain_2; int /*<<< orphan*/  hdr; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {int chain_noise_scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAIN_NOISE_MAX_DELTA_GAIN_CODE ; 
 int /*<<< orphan*/  CMD_ASYNC ; 
 int /*<<< orphan*/  IWL_CHAIN_NOISE_CALIBRATED ; 
 int /*<<< orphan*/  IWL_DEBUG_CALIB (struct iwl_priv*,char*,int,int) ; 
 int NUM_RX_CHAINS ; 
 int /*<<< orphan*/  REPLY_PHY_CALIBRATION_CMD ; 
 int /*<<< orphan*/  abs (int) ; 
 int /*<<< orphan*/  iwl_dvm_send_cmd_pdu (struct iwl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_calib_chain_noise_gain_cmd*) ; 
 int /*<<< orphan*/  iwl_set_calib_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct iwl_calib_chain_noise_gain_cmd*,int /*<<< orphan*/ ,int) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwlagn_gain_computation(struct iwl_priv *priv,
				    u32 average_noise[NUM_RX_CHAINS],
				    u8 default_chain)
{
	int i;
	s32 delta_g;
	struct iwl_chain_noise_data *data = &priv->chain_noise_data;

	/*
	 * Find Gain Code for the chains based on "default chain"
	 */
	for (i = default_chain + 1; i < NUM_RX_CHAINS; i++) {
		if ((data->disconn_array[i])) {
			data->delta_gain_code[i] = 0;
			continue;
		}

		delta_g = (priv->lib->chain_noise_scale *
			((s32)average_noise[default_chain] -
			(s32)average_noise[i])) / 1500;

		/* bound gain by 2 bits value max, 3rd bit is sign */
		data->delta_gain_code[i] =
			min(abs(delta_g), CHAIN_NOISE_MAX_DELTA_GAIN_CODE);

		if (delta_g < 0)
			/*
			 * set negative sign ...
			 * note to Intel developers:  This is uCode API format,
			 *   not the format of any internal device registers.
			 *   Do not change this format for e.g. 6050 or similar
			 *   devices.  Change format only if more resolution
			 *   (i.e. more than 2 bits magnitude) is needed.
			 */
			data->delta_gain_code[i] |= (1 << 2);
	}

	IWL_DEBUG_CALIB(priv, "Delta gains: ANT_B = %d  ANT_C = %d\n",
			data->delta_gain_code[1], data->delta_gain_code[2]);

	if (!data->radio_write) {
		struct iwl_calib_chain_noise_gain_cmd cmd;

		memset(&cmd, 0, sizeof(cmd));

		iwl_set_calib_hdr(&cmd.hdr,
			priv->phy_calib_chain_noise_gain_cmd);
		cmd.delta_gain_1 = data->delta_gain_code[1];
		cmd.delta_gain_2 = data->delta_gain_code[2];
		iwl_dvm_send_cmd_pdu(priv, REPLY_PHY_CALIBRATION_CMD,
			CMD_ASYNC, sizeof(cmd), &cmd);

		data->radio_write = 1;
		data->state = IWL_CHAIN_NOISE_CALIBRATED;
	}
}