#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ data; } ;
struct rtllib_hdr_3addr {int /*<<< orphan*/  addr2; int /*<<< orphan*/  frame_ctl; int /*<<< orphan*/  addr3; } ;
struct rtllib_disassoc {int /*<<< orphan*/  reason; } ;
struct TYPE_6__ {int bBusyTraffic; } ;
struct TYPE_5__ {int /*<<< orphan*/  reassoc; } ;
struct TYPE_4__ {int /*<<< orphan*/  bssid; } ;
struct rtllib_device {int softmac_features; scalar_t__ state; scalar_t__ iw_mode; int is_roaming; int (* rtllib_ap_sec_type ) (struct rtllib_device*) ;int /*<<< orphan*/  associate_procedure_wq; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* LedControlHandler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_3__ LinkDetectInfo; TYPE_2__ softmac_stats; TYPE_1__ current_network; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int IEEE_SOFTMAC_ASSOCIATE ; 
 scalar_t__ IW_MODE_INFRA ; 
 int /*<<< orphan*/  LED_CTL_START_TO_LINK ; 
 scalar_t__ RTLLIB_ASSOCIATING ; 
 scalar_t__ RTLLIB_LINKED ; 
 int /*<<< orphan*/  RemovePeerTS (struct rtllib_device*,int /*<<< orphan*/ ) ; 
 int SEC_ALG_CCMP ; 
 int SEC_ALG_TKIP ; 
 int /*<<< orphan*/  WLAN_FC_GET_STYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtllib_disassociate (struct rtllib_device*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct rtllib_device*) ; 

__attribute__((used)) static inline int
rtllib_rx_deauth(struct rtllib_device *ieee, struct sk_buff *skb)
{
	struct rtllib_hdr_3addr *header = (struct rtllib_hdr_3addr *) skb->data;
	u16 frame_ctl;

	if (memcmp(header->addr3, ieee->current_network.bssid, ETH_ALEN) != 0)
		return 0;

	/* FIXME for now repeat all the association procedure
	 * both for disassociation and deauthentication
	 */
	if ((ieee->softmac_features & IEEE_SOFTMAC_ASSOCIATE) &&
	    ieee->state == RTLLIB_LINKED &&
	    (ieee->iw_mode == IW_MODE_INFRA)) {
		frame_ctl = le16_to_cpu(header->frame_ctl);
		netdev_info(ieee->dev,
			    "==========>received disassoc/deauth(%x) frame, reason code:%x\n",
			    WLAN_FC_GET_STYPE(frame_ctl),
			    ((struct rtllib_disassoc *)skb->data)->reason);
		ieee->state = RTLLIB_ASSOCIATING;
		ieee->softmac_stats.reassoc++;
		ieee->is_roaming = true;
		ieee->LinkDetectInfo.bBusyTraffic = false;
		rtllib_disassociate(ieee);
		RemovePeerTS(ieee, header->addr2);
		if (ieee->LedControlHandler != NULL)
			ieee->LedControlHandler(ieee->dev,
						LED_CTL_START_TO_LINK);

		if (!(ieee->rtllib_ap_sec_type(ieee) &
		    (SEC_ALG_CCMP|SEC_ALG_TKIP)))
			schedule_delayed_work(
				       &ieee->associate_procedure_wq, 5);
	}
	return 0;
}