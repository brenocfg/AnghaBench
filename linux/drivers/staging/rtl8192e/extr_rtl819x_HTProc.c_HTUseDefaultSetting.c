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
struct TYPE_3__ {int /*<<< orphan*/  supported; int /*<<< orphan*/  active; } ;
struct TYPE_4__ {TYPE_1__ qos_data; } ;
struct rtllib_device {scalar_t__ iw_mode; int /*<<< orphan*/  HTHighestOperaRate; int /*<<< orphan*/  HTCurrentOperaRate; int /*<<< orphan*/  dot11HTOperationalRateSet; int /*<<< orphan*/  Regdot11TxHTOperationalRateSet; TYPE_2__ current_network; struct rt_hi_throughput* pHTInfo; } ;
struct rt_hi_throughput {int bCurrentHTSupport; int /*<<< orphan*/  CurrentMPDUDensity; int /*<<< orphan*/  AMPDU_Factor; int /*<<< orphan*/  CurrentAMPDUFactor; int /*<<< orphan*/  bAMPDUEnable; int /*<<< orphan*/  bCurrentAMPDUEnable; int /*<<< orphan*/  nAMSDU_MaxSize; int /*<<< orphan*/  nCurrent_AMSDU_MaxSize; int /*<<< orphan*/  bAMSDU_Support; int /*<<< orphan*/  bCurrent_AMSDU_Support; int /*<<< orphan*/  bRegShortGI40MHz; int /*<<< orphan*/  bCurShortGI40MHz; int /*<<< orphan*/  bRegShortGI20MHz; int /*<<< orphan*/  bCurShortGI20MHz; int /*<<< orphan*/  bRegBW40MHz; int /*<<< orphan*/  bCurBW40MHz; int /*<<< orphan*/  bRegSuppCCK; int /*<<< orphan*/  bCurSuppCCK; scalar_t__ bEnableHT; } ;

/* Variables and functions */
 int /*<<< orphan*/  HTFilterMCSRate (struct rtllib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HTGetHighestMCSRate (struct rtllib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IW_MODE_ADHOC ; 
 int /*<<< orphan*/  MCS_FILTER_ALL ; 

void HTUseDefaultSetting(struct rtllib_device *ieee)
{
	struct rt_hi_throughput *pHTInfo = ieee->pHTInfo;

	if (pHTInfo->bEnableHT) {
		pHTInfo->bCurrentHTSupport = true;
		pHTInfo->bCurSuppCCK = pHTInfo->bRegSuppCCK;

		pHTInfo->bCurBW40MHz = pHTInfo->bRegBW40MHz;
		pHTInfo->bCurShortGI20MHz = pHTInfo->bRegShortGI20MHz;

		pHTInfo->bCurShortGI40MHz = pHTInfo->bRegShortGI40MHz;

		if (ieee->iw_mode == IW_MODE_ADHOC)
			ieee->current_network.qos_data.active =
				 ieee->current_network.qos_data.supported;
		pHTInfo->bCurrent_AMSDU_Support = pHTInfo->bAMSDU_Support;
		pHTInfo->nCurrent_AMSDU_MaxSize = pHTInfo->nAMSDU_MaxSize;

		pHTInfo->bCurrentAMPDUEnable = pHTInfo->bAMPDUEnable;
		pHTInfo->CurrentAMPDUFactor = pHTInfo->AMPDU_Factor;

		pHTInfo->CurrentMPDUDensity = pHTInfo->CurrentMPDUDensity;

		HTFilterMCSRate(ieee, ieee->Regdot11TxHTOperationalRateSet,
				ieee->dot11HTOperationalRateSet);
		ieee->HTHighestOperaRate = HTGetHighestMCSRate(ieee,
					   ieee->dot11HTOperationalRateSet,
					   MCS_FILTER_ALL);
		ieee->HTCurrentOperaRate = ieee->HTHighestOperaRate;

	} else {
		pHTInfo->bCurrentHTSupport = false;
	}
}