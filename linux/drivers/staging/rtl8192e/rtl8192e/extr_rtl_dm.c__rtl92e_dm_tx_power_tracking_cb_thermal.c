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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct r8192_priv {int btxpower_trackingInit; scalar_t__* OFDM_index; scalar_t__ CCK_index; scalar_t__* ThermalMeter; scalar_t__ CurrentChannelBW; size_t Record_CCK_20Mindex; scalar_t__ Record_CCK_40Mindex; int bcck_in_ch14; scalar_t__ txpower_count; TYPE_2__* rtllib; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int channel; } ;
struct TYPE_4__ {TYPE_1__ current_network; } ;

/* Variables and functions */
 scalar_t__** CCKSwingTable_Ch1_Ch13 ; 
 int CCK_Table_length ; 
 int /*<<< orphan*/  COMP_POWER_TRACKING ; 
 scalar_t__ HT_CHANNEL_WIDTH_20 ; 
 scalar_t__* OFDMSwingTable ; 
 int OFDM_Table_Length ; 
 int /*<<< orphan*/  RF90_PATH_A ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,size_t,...) ; 
 void* ThermalMeterVal ; 
 int /*<<< orphan*/  bMaskByte2 ; 
 int /*<<< orphan*/  bMaskDWord ; 
 int /*<<< orphan*/  rCCK0_TxFilter1 ; 
 int /*<<< orphan*/  rOFDM0_XATxIQImbalance ; 
 int /*<<< orphan*/  rtl92e_dm_cck_txpower_adjust (struct net_device*,int) ; 
 scalar_t__ rtl92e_get_bb_reg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rtl92e_get_rf_reg (struct net_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtl92e_set_bb_reg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_dm_tx_power_tracking_cb_thermal(struct net_device *dev)
{
#define ThermalMeterVal	9
	struct r8192_priv *priv = rtllib_priv(dev);
	u32 tmpRegA, TempCCk;
	u8 tmpOFDMindex, tmpCCKindex, tmpCCK20Mindex, tmpCCK40Mindex, tmpval;
	int i = 0, CCKSwingNeedUpdate = 0;

	if (!priv->btxpower_trackingInit) {
		tmpRegA = rtl92e_get_bb_reg(dev, rOFDM0_XATxIQImbalance,
					    bMaskDWord);
		for (i = 0; i < OFDM_Table_Length; i++) {
			if (tmpRegA == OFDMSwingTable[i]) {
				priv->OFDM_index[0] = (u8)i;
				RT_TRACE(COMP_POWER_TRACKING,
					 "Initial reg0x%x = 0x%x, OFDM_index = 0x%x\n",
					 rOFDM0_XATxIQImbalance, tmpRegA,
					 priv->OFDM_index[0]);
			}
		}

		TempCCk = rtl92e_get_bb_reg(dev, rCCK0_TxFilter1, bMaskByte2);
		for (i = 0; i < CCK_Table_length; i++) {
			if (TempCCk == (u32)CCKSwingTable_Ch1_Ch13[i][0]) {
				priv->CCK_index = (u8) i;
				RT_TRACE(COMP_POWER_TRACKING,
					 "Initial reg0x%x = 0x%x, CCK_index = 0x%x\n",
					 rCCK0_TxFilter1, TempCCk,
					 priv->CCK_index);
				break;
			}
		}
		priv->btxpower_trackingInit = true;
		return;
	}

	tmpRegA = rtl92e_get_rf_reg(dev, RF90_PATH_A, 0x12, 0x078);
	RT_TRACE(COMP_POWER_TRACKING, "Readback ThermalMeterA = %d\n", tmpRegA);
	if (tmpRegA < 3 || tmpRegA > 13)
		return;
	if (tmpRegA >= 12)
		tmpRegA = 12;
	RT_TRACE(COMP_POWER_TRACKING, "Valid ThermalMeterA = %d\n", tmpRegA);
	priv->ThermalMeter[0] = ThermalMeterVal;
	priv->ThermalMeter[1] = ThermalMeterVal;

	if (priv->ThermalMeter[0] >= (u8)tmpRegA) {
		tmpOFDMindex = tmpCCK20Mindex = 6+(priv->ThermalMeter[0] -
			      (u8)tmpRegA);
		tmpCCK40Mindex = tmpCCK20Mindex - 6;
		if (tmpOFDMindex >= OFDM_Table_Length)
			tmpOFDMindex = OFDM_Table_Length-1;
		if (tmpCCK20Mindex >= CCK_Table_length)
			tmpCCK20Mindex = CCK_Table_length-1;
		if (tmpCCK40Mindex >= CCK_Table_length)
			tmpCCK40Mindex = CCK_Table_length-1;
	} else {
		tmpval = (u8)tmpRegA - priv->ThermalMeter[0];
		if (tmpval >= 6) {
			tmpOFDMindex = 0;
			tmpCCK20Mindex = 0;
		} else {
			tmpOFDMindex = 6 - tmpval;
			tmpCCK20Mindex = 6 - tmpval;
		}
		tmpCCK40Mindex = 0;
	}
	if (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20)
		tmpCCKindex = tmpCCK40Mindex;
	else
		tmpCCKindex = tmpCCK20Mindex;

	priv->Record_CCK_20Mindex = tmpCCK20Mindex;
	priv->Record_CCK_40Mindex = tmpCCK40Mindex;
	RT_TRACE(COMP_POWER_TRACKING,
		 "Record_CCK_20Mindex / Record_CCK_40Mindex = %d / %d.\n",
		 priv->Record_CCK_20Mindex, priv->Record_CCK_40Mindex);

	if (priv->rtllib->current_network.channel == 14 &&
	    !priv->bcck_in_ch14) {
		priv->bcck_in_ch14 = true;
		CCKSwingNeedUpdate = 1;
	} else if (priv->rtllib->current_network.channel != 14 &&
		   priv->bcck_in_ch14) {
		priv->bcck_in_ch14 = false;
		CCKSwingNeedUpdate = 1;
	}

	if (priv->CCK_index != tmpCCKindex) {
		priv->CCK_index = tmpCCKindex;
		CCKSwingNeedUpdate = 1;
	}

	if (CCKSwingNeedUpdate)
		rtl92e_dm_cck_txpower_adjust(dev, priv->bcck_in_ch14);
	if (priv->OFDM_index[0] != tmpOFDMindex) {
		priv->OFDM_index[0] = tmpOFDMindex;
		rtl92e_set_bb_reg(dev, rOFDM0_XATxIQImbalance, bMaskDWord,
				  OFDMSwingTable[priv->OFDM_index[0]]);
		RT_TRACE(COMP_POWER_TRACKING, "Update OFDMSwing[%d] = 0x%x\n",
			 priv->OFDM_index[0],
			 OFDMSwingTable[priv->OFDM_index[0]]);
	}
	priv->txpower_count = 0;
}