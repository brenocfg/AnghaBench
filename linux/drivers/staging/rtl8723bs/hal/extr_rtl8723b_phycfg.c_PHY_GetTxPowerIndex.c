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
typedef  int /*<<< orphan*/  u8 ;
struct hal_com_data {int /*<<< orphan*/  CurrentChannel; int /*<<< orphan*/  CurrentChannelBW; } ;
struct TYPE_2__ {int /*<<< orphan*/  RegPwrTblSel; } ;
struct adapter {TYPE_1__ registrypriv; } ;
typedef  scalar_t__ s8 ;
typedef  enum CHANNEL_WIDTH { ____Placeholder_CHANNEL_WIDTH } CHANNEL_WIDTH ;

/* Variables and functions */
 int /*<<< orphan*/  BAND_ON_2_4G ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 scalar_t__ MAX_POWER_INDEX ; 
 int /*<<< orphan*/  ODM_RF_PATH_A ; 
 scalar_t__ PHY_GetTxPowerByRate (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PHY_GetTxPowerIndexBase (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ PHY_GetTxPowerTrackingOffset (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_1TX ; 
 scalar_t__ phy_get_tx_pwr_lmt (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u8 PHY_GetTxPowerIndex(
	struct adapter *padapter,
	u8 RFPath,
	u8 Rate,
	enum CHANNEL_WIDTH BandWidth,
	u8 Channel
)
{
	struct hal_com_data *pHalData = GET_HAL_DATA(padapter);
	s8 txPower = 0, powerDiffByRate = 0, limit = 0;
	bool bIn24G = false;

	/* DBG_871X("===>%s\n", __func__); */

	txPower = (s8) PHY_GetTxPowerIndexBase(padapter, RFPath, Rate, BandWidth, Channel, &bIn24G);
	powerDiffByRate = PHY_GetTxPowerByRate(padapter, BAND_ON_2_4G, ODM_RF_PATH_A, RF_1TX, Rate);

	limit = phy_get_tx_pwr_lmt(
		padapter,
		padapter->registrypriv.RegPwrTblSel,
		(u8)(!bIn24G),
		pHalData->CurrentChannelBW,
		RFPath,
		Rate,
		pHalData->CurrentChannel
	);

	powerDiffByRate = powerDiffByRate > limit ? limit : powerDiffByRate;
	txPower += powerDiffByRate;

	txPower += PHY_GetTxPowerTrackingOffset(padapter, RFPath, Rate);

	if (txPower > MAX_POWER_INDEX)
		txPower = MAX_POWER_INDEX;

	/* DBG_871X("Final Tx Power(RF-%c, Channel: %d) = %d(0x%X)\n", ((RFPath == 0)?'A':'B'), Channel, txPower, txPower)); */
	return (u8) txPower;
}