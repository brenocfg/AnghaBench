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
struct TYPE_4__ {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_family; } ;
union iwreq_data {TYPE_2__ ap_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  bssid; } ;
struct rtllib_device {scalar_t__ iw_mode; scalar_t__ state; scalar_t__ wap_set; int /*<<< orphan*/  lock; TYPE_1__ current_network; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ IW_MODE_MONITOR ; 
 scalar_t__ RTLLIB_LINKED ; 
 scalar_t__ RTLLIB_LINKED_SCANNING ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int rtllib_wx_get_wap(struct rtllib_device *ieee,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu, char *extra)
{
	unsigned long flags;

	wrqu->ap_addr.sa_family = ARPHRD_ETHER;

	if (ieee->iw_mode == IW_MODE_MONITOR)
		return -1;

	/* We want avoid to give to the user inconsistent infos*/
	spin_lock_irqsave(&ieee->lock, flags);

	if (ieee->state != RTLLIB_LINKED &&
		ieee->state != RTLLIB_LINKED_SCANNING &&
		ieee->wap_set == 0)

		eth_zero_addr(wrqu->ap_addr.sa_data);
	else
		memcpy(wrqu->ap_addr.sa_data,
		       ieee->current_network.bssid, ETH_ALEN);

	spin_unlock_irqrestore(&ieee->lock, flags);

	return 0;
}