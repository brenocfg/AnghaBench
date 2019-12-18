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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rtw_dev {int dummy; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rtw_build_rsvd_page (struct rtw_dev*,struct ieee80211_vif*,int /*<<< orphan*/ *) ; 
 int rtw_download_beacon (struct rtw_dev*,struct ieee80211_vif*) ; 
 int rtw_download_drv_rsvd_page (struct rtw_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 

int rtw_fw_download_rsvd_page(struct rtw_dev *rtwdev, struct ieee80211_vif *vif)
{
	u8 *buf;
	u32 size;
	int ret;

	buf = rtw_build_rsvd_page(rtwdev, vif, &size);
	if (!buf) {
		rtw_err(rtwdev, "failed to build rsvd page pkt\n");
		return -ENOMEM;
	}

	ret = rtw_download_drv_rsvd_page(rtwdev, buf, size);
	if (ret) {
		rtw_err(rtwdev, "failed to download drv rsvd page\n");
		goto free;
	}

	ret = rtw_download_beacon(rtwdev, vif);
	if (ret) {
		rtw_err(rtwdev, "failed to download beacon\n");
		goto free;
	}

free:
	kfree(buf);

	return ret;
}