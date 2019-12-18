#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ssid_len; int /*<<< orphan*/  channel; int /*<<< orphan*/  bssid; int /*<<< orphan*/  ssid; } ;
struct rtllib_device {int assoc_id; int ssid_set; TYPE_2__* dev; int /*<<< orphan*/  (* data_hard_resume ) (TYPE_2__*) ;int /*<<< orphan*/  (* link_change ) (TYPE_2__*) ;int /*<<< orphan*/  state; TYPE_1__ current_network; int /*<<< orphan*/  (* set_chan ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IW_ESSID_MAX_SIZE ; 
 int /*<<< orphan*/  RTLLIB_DEFAULT_TX_ESSID ; 
 int /*<<< orphan*/  RTLLIB_LINKED ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (TYPE_2__*) ; 
 int /*<<< orphan*/  notify_wx_assoc_event (struct rtllib_device*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*) ; 

__attribute__((used)) static void rtllib_start_master_bss(struct rtllib_device *ieee)
{
	ieee->assoc_id = 1;

	if (ieee->current_network.ssid_len == 0) {
		strncpy(ieee->current_network.ssid,
			RTLLIB_DEFAULT_TX_ESSID,
			IW_ESSID_MAX_SIZE);

		ieee->current_network.ssid_len =
				 strlen(RTLLIB_DEFAULT_TX_ESSID);
		ieee->ssid_set = 1;
	}

	ether_addr_copy(ieee->current_network.bssid, ieee->dev->dev_addr);

	ieee->set_chan(ieee->dev, ieee->current_network.channel);
	ieee->state = RTLLIB_LINKED;
	ieee->link_change(ieee->dev);
	notify_wx_assoc_event(ieee);

	if (ieee->data_hard_resume)
		ieee->data_hard_resume(ieee->dev);

	netif_carrier_on(ieee->dev);
}