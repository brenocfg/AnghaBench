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
struct rtllib_device {int basic_rate; scalar_t__ mode; struct rt_hi_throughput* pHTInfo; } ;
struct rt_hi_throughput {int IOTAction; int /*<<< orphan*/  bCurSuppCCK; } ;

/* Variables and functions */
 int HT_IOT_ACT_MGNT_USE_CCK_6M ; 
 scalar_t__ IEEE_A ; 
 scalar_t__ IEEE_N_24G ; 
 scalar_t__ IEEE_N_5G ; 

__attribute__((used)) static u8 MgntQuery_MgntFrameTxRate(struct rtllib_device *ieee)
{
	struct rt_hi_throughput *pHTInfo = ieee->pHTInfo;
	u8 rate;

	if (pHTInfo->IOTAction & HT_IOT_ACT_MGNT_USE_CCK_6M)
		rate = 0x0c;
	else
		rate = ieee->basic_rate & 0x7f;

	if (rate == 0) {
		if (ieee->mode == IEEE_A ||
		   ieee->mode == IEEE_N_5G ||
		   (ieee->mode == IEEE_N_24G && !pHTInfo->bCurSuppCCK))
			rate = 0x0c;
		else
			rate = 0x02;
	}

	return rate;
}