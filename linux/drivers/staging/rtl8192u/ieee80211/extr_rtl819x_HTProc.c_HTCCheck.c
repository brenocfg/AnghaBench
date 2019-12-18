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
struct ieee80211_device {TYPE_1__* pHTInfo; } ;
struct TYPE_2__ {scalar_t__ bCurrentHTSupport; } ;

/* Variables and functions */
 scalar_t__ Frame_Order (int*) ; 
 int /*<<< orphan*/  IEEE80211_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IEEE80211_DL_HT ; 
 scalar_t__ IsQoSDataFrame (int*) ; 

u8 HTCCheck(struct ieee80211_device *ieee, u8 *pFrame)
{
	if (ieee->pHTInfo->bCurrentHTSupport) {
		if ((IsQoSDataFrame(pFrame) && Frame_Order(pFrame)) == 1) {
			IEEE80211_DEBUG(IEEE80211_DL_HT, "HT CONTROL FILED EXIST!!\n");
			return true;
		}
	}
	return false;
}