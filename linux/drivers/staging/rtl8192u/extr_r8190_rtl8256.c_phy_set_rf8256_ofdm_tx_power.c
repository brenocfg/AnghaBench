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
typedef  int u16 ;
struct r8192_priv {int TxPowerDiff; int* MCSTxPowerLevelOriginalOffset; int Pwr_Track; scalar_t__ bDynamicTxHighPower; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int,int,int) ; 

void phy_set_rf8256_ofdm_tx_power(struct net_device *dev, u8 powerlevel)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	/* Joseph TxPower for 8192 testing */
	u32 writeVal, powerBase0, powerBase1, writeVal_tmp;
	u8 index = 0;
	u16 RegOffset[6] = {0xe00, 0xe04, 0xe10, 0xe14, 0xe18, 0xe1c};
	u8 byte0, byte1, byte2, byte3;

	powerBase0 = powerlevel + priv->TxPowerDiff;	/* OFDM rates */
	powerBase0 = (powerBase0 << 24) | (powerBase0 << 16) | (powerBase0 << 8) | powerBase0;
	powerBase1 = powerlevel;							/* MCS rates */
	powerBase1 = (powerBase1 << 24) | (powerBase1 << 16) | (powerBase1 << 8) | powerBase1;

	for (index = 0; index < 6; index++) {
		writeVal = priv->MCSTxPowerLevelOriginalOffset[index] + ((index < 2) ? powerBase0 : powerBase1);
		byte0 = (u8)(writeVal & 0x7f);
		byte1 = (u8)((writeVal & 0x7f00) >> 8);
		byte2 = (u8)((writeVal & 0x7f0000) >> 16);
		byte3 = (u8)((writeVal & 0x7f000000) >> 24);

		if (byte0 > 0x24)
			/* Max power index = 0x24 */
			byte0 = 0x24;
		if (byte1 > 0x24)
			byte1 = 0x24;
		if (byte2 > 0x24)
			byte2 = 0x24;
		if (byte3 > 0x24)
			byte3 = 0x24;

		/* for tx power track */
		if (index == 3) {
			writeVal_tmp = (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0;
			priv->Pwr_Track = writeVal_tmp;
		}

		if (priv->bDynamicTxHighPower) {
			/*Add by Jacken 2008/03/06
			 *Emily, 20080613. Set low tx power for both MCS and legacy OFDM
			 */
			writeVal = 0x03030303;
		} else {
			writeVal = (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0;
		}
		rtl8192_setBBreg(dev, RegOffset[index], 0x7f7f7f7f, writeVal);
	}
	return;
}