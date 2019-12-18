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
struct TYPE_2__ {int /*<<< orphan*/  rcr; } ;
struct rtw_dev {int /*<<< orphan*/  watch_dog_work; int /*<<< orphan*/  hw; TYPE_1__ hal; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_RCR ; 
 int /*<<< orphan*/  RTW_FLAG_RUNNING ; 
 int /*<<< orphan*/  RTW_WATCH_DOG_DELAY_TIME ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_flag_set (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int rtw_power_on (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_sec_enable_sec_engine (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rtw_core_start(struct rtw_dev *rtwdev)
{
	int ret;

	ret = rtw_power_on(rtwdev);
	if (ret)
		return ret;

	rtw_sec_enable_sec_engine(rtwdev);

	/* rcr reset after powered on */
	rtw_write32(rtwdev, REG_RCR, rtwdev->hal.rcr);

	ieee80211_queue_delayed_work(rtwdev->hw, &rtwdev->watch_dog_work,
				     RTW_WATCH_DOG_DELAY_TIME);

	rtw_flag_set(rtwdev, RTW_FLAG_RUNNING);

	return 0;
}