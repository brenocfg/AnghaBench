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
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTW_FLAG_INACTIVE_PS ; 
 int rtw_core_start (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 
 int /*<<< orphan*/  rtw_flag_clear (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_set_channel (struct rtw_dev*) ; 

__attribute__((used)) static int rtw_ips_pwr_up(struct rtw_dev *rtwdev)
{
	int ret;

	ret = rtw_core_start(rtwdev);
	if (ret)
		rtw_err(rtwdev, "leave idle state failed\n");

	rtw_set_channel(rtwdev);
	rtw_flag_clear(rtwdev, RTW_FLAG_INACTIVE_PS);

	return ret;
}