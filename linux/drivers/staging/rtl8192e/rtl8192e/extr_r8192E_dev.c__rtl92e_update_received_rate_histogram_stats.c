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
typedef  size_t u32 ;
struct rtllib_rx_stats {int rate; scalar_t__ bShortPreamble; scalar_t__ bICV; scalar_t__ bCRC; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** received_rate_histogram; int /*<<< orphan*/ ** received_preamble_GI; } ;
struct r8192_priv {TYPE_1__ stats; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
#define  MGN_11M 155 
#define  MGN_12M 154 
#define  MGN_18M 153 
#define  MGN_1M 152 
#define  MGN_24M 151 
#define  MGN_2M 150 
#define  MGN_36M 149 
#define  MGN_48M 148 
#define  MGN_54M 147 
#define  MGN_5_5M 146 
#define  MGN_6M 145 
#define  MGN_9M 144 
#define  MGN_MCS0 143 
#define  MGN_MCS1 142 
#define  MGN_MCS10 141 
#define  MGN_MCS11 140 
#define  MGN_MCS12 139 
#define  MGN_MCS13 138 
#define  MGN_MCS14 137 
#define  MGN_MCS15 136 
#define  MGN_MCS2 135 
#define  MGN_MCS3 134 
#define  MGN_MCS4 133 
#define  MGN_MCS5 132 
#define  MGN_MCS6 131 
#define  MGN_MCS7 130 
#define  MGN_MCS8 129 
#define  MGN_MCS9 128 
 scalar_t__ rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_update_received_rate_histogram_stats(
					   struct net_device *dev,
					   struct rtllib_rx_stats *pstats)
{
	struct r8192_priv *priv = (struct r8192_priv *)rtllib_priv(dev);
	u32 rcvType = 1;
	u32 rateIndex;
	u32 preamble_guardinterval;

	if (pstats->bCRC)
		rcvType = 2;
	else if (pstats->bICV)
		rcvType = 3;

	if (pstats->bShortPreamble)
		preamble_guardinterval = 1;
	else
		preamble_guardinterval = 0;

	switch (pstats->rate) {
	case MGN_1M:
		rateIndex = 0;
		break;
	case MGN_2M:
		rateIndex = 1;
		break;
	case MGN_5_5M:
		rateIndex = 2;
		break;
	case MGN_11M:
		rateIndex = 3;
		break;
	case MGN_6M:
		rateIndex = 4;
		break;
	case MGN_9M:
		rateIndex = 5;
		break;
	case MGN_12M:
		rateIndex = 6;
		break;
	case MGN_18M:
		rateIndex = 7;
		break;
	case MGN_24M:
		rateIndex = 8;
		break;
	case MGN_36M:
		rateIndex = 9;
		break;
	case MGN_48M:
		rateIndex = 10;
		break;
	case MGN_54M:
		rateIndex = 11;
		break;
	case MGN_MCS0:
		rateIndex = 12;
		break;
	case MGN_MCS1:
		rateIndex = 13;
		break;
	case MGN_MCS2:
		rateIndex = 14;
		break;
	case MGN_MCS3:
		rateIndex = 15;
		break;
	case MGN_MCS4:
		rateIndex = 16;
		break;
	case MGN_MCS5:
		rateIndex = 17;
		break;
	case MGN_MCS6:
		rateIndex = 18;
		break;
	case MGN_MCS7:
		rateIndex = 19;
		break;
	case MGN_MCS8:
		rateIndex = 20;
		break;
	case MGN_MCS9:
		rateIndex = 21;
		break;
	case MGN_MCS10:
		rateIndex = 22;
		break;
	case MGN_MCS11:
		rateIndex = 23;
		break;
	case MGN_MCS12:
		rateIndex = 24;
		break;
	case MGN_MCS13:
		rateIndex = 25;
		break;
	case MGN_MCS14:
		rateIndex = 26;
		break;
	case MGN_MCS15:
		rateIndex = 27;
		break;
	default:
		rateIndex = 28;
		break;
	}
	priv->stats.received_preamble_GI[preamble_guardinterval][rateIndex]++;
	priv->stats.received_rate_histogram[0][rateIndex]++;
	priv->stats.received_rate_histogram[rcvType][rateIndex]++;
}