#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct tx_config_cmd {int cmd_length; scalar_t__ cmd_value; int /*<<< orphan*/  cmd_op; } ;
struct r8192_priv {int Pwr_Track; int rf_type; scalar_t__ TSSI_13dBm; int rfa_txpowertrackingindex; int rfa_txpowertrackingindex_real; int cck_present_attenuation_difference; int cck_present_attenuation; int rfa_txpowertracking_default; scalar_t__ CurrentChannelBW; int cck_present_attenuation_20Mdefault; int cck_present_attenuation_40Mdefault; int bcck_in_ch14; TYPE_2__* ieee80211; TYPE_3__* txbbgain_table; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  txbbgain_value; } ;
struct TYPE_4__ {int channel; } ;
struct TYPE_5__ {int bdynamic_txpower_enable; TYPE_1__ current_network; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_POWER_TRACKING ; 
 scalar_t__ E_FOR_TX_POWER_TRACK ; 
 scalar_t__ HT_CHANNEL_WIDTH_20 ; 
 int RT_STATUS_FAILURE ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 int SendTxCommandPacket (struct net_device*,struct tx_config_cmd*,int) ; 
 int /*<<< orphan*/  TXCMD_SET_TX_PWR_TRACKING ; 
 int /*<<< orphan*/  bMaskDWord ; 
 int /*<<< orphan*/  dm_cck_txpower_adjust (struct net_device*,int) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rOFDM0_XATxIQImbalance ; 
 int /*<<< orphan*/  read_nic_byte (struct net_device*,int,int*) ; 
 int /*<<< orphan*/  read_nic_word (struct net_device*,int,scalar_t__*) ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_TXPowerTrackingCallback_TSSI(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	bool						viviflag = false;
	struct tx_config_cmd			        tx_cmd;
	u8						powerlevelOFDM24G;
	int						i = 0, j = 0, k = 0;
	u8						RF_Type, tmp_report[5] = {0, 0, 0, 0, 0};
	u32						Value;
	u8						Pwr_Flag;
	u16						Avg_TSSI_Meas, TSSI_13dBm, Avg_TSSI_Meas_from_driver = 0;
	/*RT_STATUS				rtStatus = RT_STATUS_SUCCESS;*/
	bool rtStatus = true;
	u32						delta = 0;

	write_nic_byte(dev, 0x1ba, 0);

	priv->ieee80211->bdynamic_txpower_enable = false;

	powerlevelOFDM24G = (u8)(priv->Pwr_Track>>24);
	RF_Type = priv->rf_type;
	Value = (RF_Type<<8) | powerlevelOFDM24G;

	RT_TRACE(COMP_POWER_TRACKING, "powerlevelOFDM24G = %x\n", powerlevelOFDM24G);

	for (j = 0; j <= 30; j++) { /* fill tx_cmd */
		tx_cmd.cmd_op = TXCMD_SET_TX_PWR_TRACKING;
		tx_cmd.cmd_length = sizeof(tx_cmd.cmd_op);
		tx_cmd.cmd_value = Value;
		rtStatus = SendTxCommandPacket(dev, &tx_cmd, sizeof(struct tx_config_cmd));
		if (rtStatus == RT_STATUS_FAILURE)
			RT_TRACE(COMP_POWER_TRACKING, "Set configuration with tx cmd queue fail!\n");
		usleep_range(1000, 2000);
		/*DbgPrint("hi, vivi, strange\n");*/
		for (i = 0; i <= 30; i++) {
			read_nic_byte(dev, 0x1ba, &Pwr_Flag);

			if (Pwr_Flag == 0) {
				usleep_range(1000, 2000);
				continue;
			}
			read_nic_word(dev, 0x13c, &Avg_TSSI_Meas);
			if (Avg_TSSI_Meas == 0) {
				write_nic_byte(dev, 0x1ba, 0);
				break;
			}

			for (k = 0; k < 5; k++) {
				if (k != 4)
					read_nic_byte(dev, 0x134+k, &tmp_report[k]);
				else
					read_nic_byte(dev, 0x13e, &tmp_report[k]);
				RT_TRACE(COMP_POWER_TRACKING, "TSSI_report_value = %d\n", tmp_report[k]);
			}

			/* check if the report value is right */
			for (k = 0; k < 5; k++) {
				if (tmp_report[k] <= 20) {
					viviflag = true;
					break;
				}
			}
			if (viviflag) {
				write_nic_byte(dev, 0x1ba, 0);
				viviflag = false;
				RT_TRACE(COMP_POWER_TRACKING, "we filtered the data\n");
				for (k = 0; k < 5; k++)
					tmp_report[k] = 0;
				break;
			}

			for (k = 0; k < 5; k++)
				Avg_TSSI_Meas_from_driver += tmp_report[k];

			Avg_TSSI_Meas_from_driver = Avg_TSSI_Meas_from_driver*100/5;
			RT_TRACE(COMP_POWER_TRACKING, "Avg_TSSI_Meas_from_driver = %d\n", Avg_TSSI_Meas_from_driver);
			TSSI_13dBm = priv->TSSI_13dBm;
			RT_TRACE(COMP_POWER_TRACKING, "TSSI_13dBm = %d\n", TSSI_13dBm);

			/*if (abs(Avg_TSSI_Meas_from_driver - TSSI_13dBm) <= E_FOR_TX_POWER_TRACK)*/
			/* For MacOS-compatible */
			if (Avg_TSSI_Meas_from_driver > TSSI_13dBm)
				delta = Avg_TSSI_Meas_from_driver - TSSI_13dBm;
			else
				delta = TSSI_13dBm - Avg_TSSI_Meas_from_driver;

			if (delta <= E_FOR_TX_POWER_TRACK) {
				priv->ieee80211->bdynamic_txpower_enable = true;
				write_nic_byte(dev, 0x1ba, 0);
				RT_TRACE(COMP_POWER_TRACKING, "tx power track is done\n");
				RT_TRACE(COMP_POWER_TRACKING, "priv->rfa_txpowertrackingindex = %d\n", priv->rfa_txpowertrackingindex);
				RT_TRACE(COMP_POWER_TRACKING, "priv->rfa_txpowertrackingindex_real = %d\n", priv->rfa_txpowertrackingindex_real);
				RT_TRACE(COMP_POWER_TRACKING, "priv->cck_present_attenuation_difference = %d\n", priv->cck_present_attenuation_difference);
				RT_TRACE(COMP_POWER_TRACKING, "priv->cck_present_attenuation = %d\n", priv->cck_present_attenuation);
				return;
			}
			if (Avg_TSSI_Meas_from_driver < TSSI_13dBm - E_FOR_TX_POWER_TRACK) {
				if (priv->rfa_txpowertrackingindex > 0) {
					priv->rfa_txpowertrackingindex--;
					if (priv->rfa_txpowertrackingindex_real > 4) {
						priv->rfa_txpowertrackingindex_real--;
						rtl8192_setBBreg(dev, rOFDM0_XATxIQImbalance, bMaskDWord, priv->txbbgain_table[priv->rfa_txpowertrackingindex_real].txbbgain_value);
					}
				}
			} else {
				if (priv->rfa_txpowertrackingindex < 36) {
					priv->rfa_txpowertrackingindex++;
					priv->rfa_txpowertrackingindex_real++;
					rtl8192_setBBreg(dev, rOFDM0_XATxIQImbalance, bMaskDWord, priv->txbbgain_table[priv->rfa_txpowertrackingindex_real].txbbgain_value);

				}
			}
			priv->cck_present_attenuation_difference
				= priv->rfa_txpowertrackingindex - priv->rfa_txpowertracking_default;

			if (priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20)
				priv->cck_present_attenuation
					= priv->cck_present_attenuation_20Mdefault + priv->cck_present_attenuation_difference;
			else
				priv->cck_present_attenuation
					= priv->cck_present_attenuation_40Mdefault + priv->cck_present_attenuation_difference;

			if (priv->cck_present_attenuation > -1 && priv->cck_present_attenuation < 23) {
				if (priv->ieee80211->current_network.channel == 14 && !priv->bcck_in_ch14) {
					priv->bcck_in_ch14 = true;
					dm_cck_txpower_adjust(dev, priv->bcck_in_ch14);
				} else if (priv->ieee80211->current_network.channel != 14 && priv->bcck_in_ch14) {
					priv->bcck_in_ch14 = false;
					dm_cck_txpower_adjust(dev, priv->bcck_in_ch14);
				} else
					dm_cck_txpower_adjust(dev, priv->bcck_in_ch14);
			}
			RT_TRACE(COMP_POWER_TRACKING, "priv->rfa_txpowertrackingindex = %d\n", priv->rfa_txpowertrackingindex);
			RT_TRACE(COMP_POWER_TRACKING, "priv->rfa_txpowertrackingindex_real = %d\n", priv->rfa_txpowertrackingindex_real);
			RT_TRACE(COMP_POWER_TRACKING, "priv->cck_present_attenuation_difference = %d\n", priv->cck_present_attenuation_difference);
			RT_TRACE(COMP_POWER_TRACKING, "priv->cck_present_attenuation = %d\n", priv->cck_present_attenuation);

			if (priv->cck_present_attenuation_difference <= -12 || priv->cck_present_attenuation_difference >= 24) {
				priv->ieee80211->bdynamic_txpower_enable = true;
				write_nic_byte(dev, 0x1ba, 0);
				RT_TRACE(COMP_POWER_TRACKING, "tx power track--->limited\n");
				return;
			}

			write_nic_byte(dev, 0x1ba, 0);
			Avg_TSSI_Meas_from_driver = 0;
			for (k = 0; k < 5; k++)
				tmp_report[k] = 0;
			break;
		}
	}
	priv->ieee80211->bdynamic_txpower_enable = true;
	write_nic_byte(dev, 0x1ba, 0);
}