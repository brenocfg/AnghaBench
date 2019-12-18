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
typedef  void* u8 ;
struct hal_com_data {int CurrentChannelBW; int nCur40MhzPrimeSC; int nCur80MhzPrimeSC; int bSwChnl; int bSetChnlBW; void* CurrentCenterFrequencyIndex1; void* CurrentChannel; } ;
struct adapter {int /*<<< orphan*/  bSurpriseRemoved; int /*<<< orphan*/  bDriverStopped; } ;
typedef  enum EXTCHNL_OFFSET { ____Placeholder_EXTCHNL_OFFSET } EXTCHNL_OFFSET ;
typedef  enum CHANNEL_WIDTH { ____Placeholder_CHANNEL_WIDTH } CHANNEL_WIDTH ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 scalar_t__ HAL_IsLegalChannel (struct adapter*,void*) ; 
 int /*<<< orphan*/  phy_SwChnlAndSetBwMode8723B (struct adapter*) ; 

__attribute__((used)) static void PHY_HandleSwChnlAndSetBW8723B(
	struct adapter *Adapter,
	bool bSwitchChannel,
	bool bSetBandWidth,
	u8 ChannelNum,
	enum CHANNEL_WIDTH ChnlWidth,
	enum EXTCHNL_OFFSET ExtChnlOffsetOf40MHz,
	enum EXTCHNL_OFFSET ExtChnlOffsetOf80MHz,
	u8 CenterFrequencyIndex1
)
{
	/* static bool		bInitialzed = false; */
	struct hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	u8 tmpChannel = pHalData->CurrentChannel;
	enum CHANNEL_WIDTH tmpBW = pHalData->CurrentChannelBW;
	u8 tmpnCur40MhzPrimeSC = pHalData->nCur40MhzPrimeSC;
	u8 tmpnCur80MhzPrimeSC = pHalData->nCur80MhzPrimeSC;
	u8 tmpCenterFrequencyIndex1 = pHalData->CurrentCenterFrequencyIndex1;

	/* DBG_871X("=> PHY_HandleSwChnlAndSetBW8812: bSwitchChannel %d, bSetBandWidth %d\n", bSwitchChannel, bSetBandWidth); */

	/* check is swchnl or setbw */
	if (!bSwitchChannel && !bSetBandWidth) {
		DBG_871X("PHY_HandleSwChnlAndSetBW8812:  not switch channel and not set bandwidth\n");
		return;
	}

	/* skip change for channel or bandwidth is the same */
	if (bSwitchChannel) {
		/* if (pHalData->CurrentChannel != ChannelNum) */
		{
			if (HAL_IsLegalChannel(Adapter, ChannelNum))
				pHalData->bSwChnl = true;
		}
	}

	if (bSetBandWidth)
		pHalData->bSetChnlBW = true;

	if (!pHalData->bSetChnlBW && !pHalData->bSwChnl) {
		/* DBG_871X("<= PHY_HandleSwChnlAndSetBW8812: bSwChnl %d, bSetChnlBW %d\n", pHalData->bSwChnl, pHalData->bSetChnlBW); */
		return;
	}


	if (pHalData->bSwChnl) {
		pHalData->CurrentChannel = ChannelNum;
		pHalData->CurrentCenterFrequencyIndex1 = ChannelNum;
	}


	if (pHalData->bSetChnlBW) {
		pHalData->CurrentChannelBW = ChnlWidth;
		pHalData->nCur40MhzPrimeSC = ExtChnlOffsetOf40MHz;
		pHalData->nCur80MhzPrimeSC = ExtChnlOffsetOf80MHz;
		pHalData->CurrentCenterFrequencyIndex1 = CenterFrequencyIndex1;
	}

	/* Switch workitem or set timer to do switch channel or setbandwidth operation */
	if ((!Adapter->bDriverStopped) && (!Adapter->bSurpriseRemoved)) {
		phy_SwChnlAndSetBwMode8723B(Adapter);
	} else {
		if (pHalData->bSwChnl) {
			pHalData->CurrentChannel = tmpChannel;
			pHalData->CurrentCenterFrequencyIndex1 = tmpChannel;
		}

		if (pHalData->bSetChnlBW) {
			pHalData->CurrentChannelBW = tmpBW;
			pHalData->nCur40MhzPrimeSC = tmpnCur40MhzPrimeSC;
			pHalData->nCur80MhzPrimeSC = tmpnCur80MhzPrimeSC;
			pHalData->CurrentCenterFrequencyIndex1 = tmpCenterFrequencyIndex1;
		}
	}
}