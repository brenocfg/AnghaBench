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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct rtw_dev {struct ieee80211_hw* hw; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct sk_buff* rtw_beacon_get (struct ieee80211_hw*,struct ieee80211_vif*) ; 
 int rtw_download_drv_rsvd_page (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 

__attribute__((used)) static int
rtw_download_beacon(struct rtw_dev *rtwdev, struct ieee80211_vif *vif)
{
	struct ieee80211_hw *hw = rtwdev->hw;
	struct sk_buff *skb;
	int ret = 0;

	skb = rtw_beacon_get(hw, vif);
	if (!skb) {
		rtw_err(rtwdev, "failed to get beacon skb\n");
		ret = -ENOMEM;
		goto out;
	}

	ret = rtw_download_drv_rsvd_page(rtwdev, skb->data, skb->len);
	if (ret)
		rtw_err(rtwdev, "failed to download drv rsvd page\n");

	dev_kfree_skb(skb);

out:
	return ret;
}