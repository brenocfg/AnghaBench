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
typedef  int u16 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int RTL_TXQ_BCN ; 
 int RTL_TXQ_BE ; 
 int RTL_TXQ_BK ; 
 int RTL_TXQ_MGT ; 
 int RTL_TXQ_VI ; 
 int RTL_TXQ_VO ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_mgmt (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

u16 rtl8192cu_mq_to_hwq(__le16 fc, u16 mac80211_queue_index)
{
	u16 hw_queue_index;

	if (unlikely(ieee80211_is_beacon(fc))) {
		hw_queue_index = RTL_TXQ_BCN;
		goto out;
	}
	if (ieee80211_is_mgmt(fc)) {
		hw_queue_index = RTL_TXQ_MGT;
		goto out;
	}
	switch (mac80211_queue_index) {
	case 0:
		hw_queue_index = RTL_TXQ_VO;
		break;
	case 1:
		hw_queue_index = RTL_TXQ_VI;
		break;
	case 2:
		hw_queue_index = RTL_TXQ_BE;
		break;
	case 3:
		hw_queue_index = RTL_TXQ_BK;
		break;
	default:
		hw_queue_index = RTL_TXQ_BE;
		WARN_ONCE(true, "rtl8192cu: QSLT_BE queue, skb_queue:%d\n",
			  mac80211_queue_index);
		break;
	}
out:
	return hw_queue_index;
}