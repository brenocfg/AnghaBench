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
struct rtllib_device {int softmac_features; int is_set_key; int /*<<< orphan*/  link_change_wq; scalar_t__ wap_set; int /*<<< orphan*/  state; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* data_hard_stop ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int IEEE_SOFTMAC_TX_QUEUE ; 
 scalar_t__ IS_DOT11D_ENABLE (struct rtllib_device*) ; 
 int /*<<< orphan*/  RTLLIB_NOLINK ; 
 int /*<<< orphan*/  dot11d_reset (struct rtllib_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_wx_assoc_event (struct rtllib_device*) ; 
 int /*<<< orphan*/  rtllib_reset_queue (struct rtllib_device*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void rtllib_disassociate(struct rtllib_device *ieee)
{
	netif_carrier_off(ieee->dev);
	if (ieee->softmac_features & IEEE_SOFTMAC_TX_QUEUE)
		rtllib_reset_queue(ieee);

	if (ieee->data_hard_stop)
		ieee->data_hard_stop(ieee->dev);
	if (IS_DOT11D_ENABLE(ieee))
		dot11d_reset(ieee);
	ieee->state = RTLLIB_NOLINK;
	ieee->is_set_key = false;
	ieee->wap_set = 0;

	schedule_delayed_work(&ieee->link_change_wq, 0);

	notify_wx_assoc_event(ieee);
}