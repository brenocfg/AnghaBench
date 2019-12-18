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
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct TYPE_2__ {int capability; scalar_t__ buseprotection; } ;
struct rtllib_device {scalar_t__ mode; scalar_t__ rts; scalar_t__ iw_mode; TYPE_1__ current_network; struct rt_hi_throughput* pHTInfo; } ;
struct rt_hi_throughput {int IOTAction; int CurrentOpMode; scalar_t__ bCurBW40MHz; scalar_t__ bEnableHT; scalar_t__ bCurrentHTSupport; } ;
struct cb_desc {int bRTSSTBC; int bRTSUseShortGI; int bCTSEnable; int bRTSBW; int bRTSEnable; int bUseShortPreamble; scalar_t__ RTSSC; void* rts_rate; scalar_t__ bAMPDUEnable; scalar_t__ bMulticast; scalar_t__ bBroadcast; } ;

/* Variables and functions */
 int HT_IOT_ACT_FORCED_CTS2SELF ; 
 int HT_IOT_ACT_FORCED_RTS ; 
 int HT_IOT_ACT_PURE_N_MODE ; 
 scalar_t__ IEEE_N_24G ; 
 scalar_t__ IW_MODE_MASTER ; 
 void* MGN_24M ; 
 int WLAN_CAPABILITY_SHORT_PREAMBLE ; 
 scalar_t__ is_broadcast_ether_addr (scalar_t__) ; 

__attribute__((used)) static void rtllib_query_protectionmode(struct rtllib_device *ieee,
					struct cb_desc *tcb_desc,
					struct sk_buff *skb)
{
	struct rt_hi_throughput *pHTInfo;

	tcb_desc->bRTSSTBC			= false;
	tcb_desc->bRTSUseShortGI		= false;
	tcb_desc->bCTSEnable			= false;
	tcb_desc->RTSSC				= 0;
	tcb_desc->bRTSBW			= false;

	if (tcb_desc->bBroadcast || tcb_desc->bMulticast)
		return;

	if (is_broadcast_ether_addr(skb->data+16))
		return;

	if (ieee->mode < IEEE_N_24G) {
		if (skb->len > ieee->rts) {
			tcb_desc->bRTSEnable = true;
			tcb_desc->rts_rate = MGN_24M;
		} else if (ieee->current_network.buseprotection) {
			tcb_desc->bRTSEnable = true;
			tcb_desc->bCTSEnable = true;
			tcb_desc->rts_rate = MGN_24M;
		}
		return;
	}

	pHTInfo = ieee->pHTInfo;

	while (true) {
		if (pHTInfo->IOTAction & HT_IOT_ACT_FORCED_CTS2SELF) {
			tcb_desc->bCTSEnable	= true;
			tcb_desc->rts_rate  =	MGN_24M;
			tcb_desc->bRTSEnable = true;
			break;
		} else if (pHTInfo->IOTAction & (HT_IOT_ACT_FORCED_RTS |
			   HT_IOT_ACT_PURE_N_MODE)) {
			tcb_desc->bRTSEnable = true;
			tcb_desc->rts_rate  =	MGN_24M;
			break;
		}
		if (ieee->current_network.buseprotection) {
			tcb_desc->bRTSEnable = true;
			tcb_desc->bCTSEnable = true;
			tcb_desc->rts_rate = MGN_24M;
			break;
		}
		if (pHTInfo->bCurrentHTSupport  && pHTInfo->bEnableHT) {
			u8 HTOpMode = pHTInfo->CurrentOpMode;

			if ((pHTInfo->bCurBW40MHz && (HTOpMode == 2 ||
			     HTOpMode == 3)) ||
			     (!pHTInfo->bCurBW40MHz && HTOpMode == 3)) {
				tcb_desc->rts_rate = MGN_24M;
				tcb_desc->bRTSEnable = true;
				break;
			}
		}
		if (skb->len > ieee->rts) {
			tcb_desc->rts_rate = MGN_24M;
			tcb_desc->bRTSEnable = true;
			break;
		}
		if (tcb_desc->bAMPDUEnable) {
			tcb_desc->rts_rate = MGN_24M;
			tcb_desc->bRTSEnable = false;
			break;
		}
		goto NO_PROTECTION;
	}
	if (ieee->current_network.capability & WLAN_CAPABILITY_SHORT_PREAMBLE)
		tcb_desc->bUseShortPreamble = true;
	if (ieee->iw_mode == IW_MODE_MASTER)
		goto NO_PROTECTION;
	return;
NO_PROTECTION:
	tcb_desc->bRTSEnable	= false;
	tcb_desc->bCTSEnable	= false;
	tcb_desc->rts_rate	= 0;
	tcb_desc->RTSSC		= 0;
	tcb_desc->bRTSBW	= false;
}