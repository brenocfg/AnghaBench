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
typedef  int u32 ;
struct r8192_priv {scalar_t__ epromtype; int* TxPowerLevelCCK; int* TxPowerLevelOFDM24G; scalar_t__ rf_type; int* TxPowerLevelCCK_C; int* TxPowerLevelOFDM24G_C; int* TxPowerLevelCCK_A; int* TxPowerLevelOFDM24G_A; int RF_C_TxPwDiff; int* AntennaTxPwDiff; int rf_chip; } ;
struct net_device {int dummy; } ;
typedef  int s8 ;

/* Variables and functions */
 scalar_t__ EEPROM_93C46 ; 
 scalar_t__ EEPROM_93C56 ; 
 scalar_t__ RF_1T2R ; 
 scalar_t__ RF_2T4R ; 
#define  RF_8225 130 
#define  RF_8256 129 
#define  RF_8258 128 
 int bXBTxAGC ; 
 int bXCTxAGC ; 
 int bXDTxAGC ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  rFPGA0_TxGainStage ; 
 int /*<<< orphan*/  rtl92e_set_bb_reg (struct net_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtl92e_set_cck_tx_power (struct net_device*,int) ; 
 int /*<<< orphan*/  rtl92e_set_ofdm_tx_power (struct net_device*,int) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

void rtl92e_set_tx_power(struct net_device *dev, u8 channel)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	u8	powerlevel = 0, powerlevelOFDM24G = 0;
	s8	ant_pwr_diff;
	u32	u4RegValue;

	if (priv->epromtype == EEPROM_93C46) {
		powerlevel = priv->TxPowerLevelCCK[channel-1];
		powerlevelOFDM24G = priv->TxPowerLevelOFDM24G[channel-1];
	} else if (priv->epromtype == EEPROM_93C56) {
		if (priv->rf_type == RF_1T2R) {
			powerlevel = priv->TxPowerLevelCCK_C[channel-1];
			powerlevelOFDM24G = priv->TxPowerLevelOFDM24G_C[channel-1];
		} else if (priv->rf_type == RF_2T4R) {
			powerlevel = priv->TxPowerLevelCCK_A[channel-1];
			powerlevelOFDM24G = priv->TxPowerLevelOFDM24G_A[channel-1];

			ant_pwr_diff = priv->TxPowerLevelOFDM24G_C[channel-1]
				       - priv->TxPowerLevelOFDM24G_A[channel-1];

			priv->RF_C_TxPwDiff = ant_pwr_diff;

			ant_pwr_diff &= 0xf;

			priv->AntennaTxPwDiff[2] = 0;
			priv->AntennaTxPwDiff[1] = (u8)(ant_pwr_diff);
			priv->AntennaTxPwDiff[0] = 0;

			u4RegValue = priv->AntennaTxPwDiff[2]<<8 |
				      priv->AntennaTxPwDiff[1]<<4 |
				      priv->AntennaTxPwDiff[0];

			rtl92e_set_bb_reg(dev, rFPGA0_TxGainStage,
					  (bXBTxAGC|bXCTxAGC|bXDTxAGC),
					  u4RegValue);
		}
	}
	switch (priv->rf_chip) {
	case RF_8225:
		break;
	case RF_8256:
		rtl92e_set_cck_tx_power(dev, powerlevel);
		rtl92e_set_ofdm_tx_power(dev, powerlevelOFDM24G);
		break;
	case RF_8258:
		break;
	default:
		netdev_err(dev, "Invalid RF Chip ID.\n");
		break;
	}
}