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
struct ieee80211_device {int* Regdot11HTOperationalRateSet; int /*<<< orphan*/  dev; scalar_t__ (* GetHalfNmodeSupportByAPsHandler ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HT_PickMCSRate (struct ieee80211_device*,int*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 HTFilterMCSRate(struct ieee80211_device *ieee, u8 *pSupportMCS,
			  u8 *pOperateMCS)
{
	u8 i = 0;

	// filter out operational rate set not supported by AP, the length of it is 16
	for (i = 0; i <= 15; i++)
		pOperateMCS[i] = ieee->Regdot11HTOperationalRateSet[i] & pSupportMCS[i];

	// TODO: adjust our operational rate set  according to our channel bandwidth, STBC and Antenna number
	/*
	 * TODO: fill suggested rate adaptive rate index and give firmware info
	 * using Tx command packet we also shall suggested the first start rate
	 * set according to our signal strength
	 */
	HT_PickMCSRate(ieee, pOperateMCS);

	// For RTL819X, if pairwisekey = wep/tkip, we support only MCS0~7.
	if (ieee->GetHalfNmodeSupportByAPsHandler(ieee->dev))
		pOperateMCS[1] = 0;

	/*
	 * For RTL819X, we support only MCS0~15.
	 * And also, we do not know how to use MCS32 now.
	 */
	for (i = 2; i <= 15; i++)
		pOperateMCS[i] = 0;

	return true;
}