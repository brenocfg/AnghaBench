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
struct TYPE_3__ {int channel; } ;
struct ieee80211_device {TYPE_1__ current_network; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* GetHalfNmodeSupportByAPsHandler ) (int /*<<< orphan*/ ) ;TYPE_2__* pHTInfo; } ;
typedef  enum ht_extension_chan_offset { ____Placeholder_ht_extension_chan_offset } ht_extension_chan_offset ;
typedef  enum ht_channel_width { ____Placeholder_ht_channel_width } ht_channel_width ;
struct TYPE_4__ {int bSwBwInProgress; int bCurBW40MHz; int CurSTAExtChnlOffset; int /*<<< orphan*/  bRegBW40MHz; } ;
typedef  TYPE_2__* PRT_HIGH_THROUGHPUT ;

/* Variables and functions */
 int /*<<< orphan*/  HTSetConnectBwModeCallback (struct ieee80211_device*) ; 
 int HT_CHANNEL_WIDTH_20_40 ; 
 int HT_EXTCHNL_OFFSET_LOWER ; 
 void* HT_EXTCHNL_OFFSET_NO_EXT ; 
 int HT_EXTCHNL_OFFSET_UPPER ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void HTSetConnectBwMode(struct ieee80211_device *ieee, enum ht_channel_width Bandwidth, enum ht_extension_chan_offset Offset)
{
	PRT_HIGH_THROUGHPUT pHTInfo = ieee->pHTInfo;
//	u32 flags = 0;

	if (!pHTInfo->bRegBW40MHz)
		return;

	// To reduce dummy operation
//	if((pHTInfo->bCurBW40MHz==false && Bandwidth==HT_CHANNEL_WIDTH_20) ||
//	   (pHTInfo->bCurBW40MHz==true && Bandwidth==HT_CHANNEL_WIDTH_20_40 && Offset==pHTInfo->CurSTAExtChnlOffset))
//		return;

//	spin_lock_irqsave(&(ieee->bw_spinlock), flags);
	if (pHTInfo->bSwBwInProgress) {
//		spin_unlock_irqrestore(&(ieee->bw_spinlock), flags);
		return;
	}
	//if in half N mode, set to 20M bandwidth please 09.08.2008 WB.
	if (Bandwidth == HT_CHANNEL_WIDTH_20_40 && (!ieee->GetHalfNmodeSupportByAPsHandler(ieee->dev))) {
			// Handle Illegal extension channel offset!!
		if (ieee->current_network.channel < 2 && Offset == HT_EXTCHNL_OFFSET_LOWER)
			Offset = HT_EXTCHNL_OFFSET_NO_EXT;
		if (Offset == HT_EXTCHNL_OFFSET_UPPER || Offset == HT_EXTCHNL_OFFSET_LOWER) {
			pHTInfo->bCurBW40MHz = true;
			pHTInfo->CurSTAExtChnlOffset = Offset;
		} else {
			pHTInfo->bCurBW40MHz = false;
			pHTInfo->CurSTAExtChnlOffset = HT_EXTCHNL_OFFSET_NO_EXT;
		}
	} else {
		pHTInfo->bCurBW40MHz = false;
		pHTInfo->CurSTAExtChnlOffset = HT_EXTCHNL_OFFSET_NO_EXT;
	}

	pHTInfo->bSwBwInProgress = true;

	/*
	 * TODO: 2007.7.13 by Emily Wait 2000ms  in order to guarantee that
	 * switching bandwidth is executed after scan is finished. It is a
	 * temporal solution because software should ganrantee the last
	 * operation of switching bandwidth is executed properlly.
	 */
	HTSetConnectBwModeCallback(ieee);

//	spin_unlock_irqrestore(&(ieee->bw_spinlock), flags);
}