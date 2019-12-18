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
 int /*<<< orphan*/  COEX_IPS_ENTER ; 
 int /*<<< orphan*/  RTW_FLAG_INACTIVE_PS ; 
 int /*<<< orphan*/  rtw_coex_ips_notify (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_core_stop (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_flag_set (struct rtw_dev*,int /*<<< orphan*/ ) ; 

int rtw_enter_ips(struct rtw_dev *rtwdev)
{
	rtw_flag_set(rtwdev, RTW_FLAG_INACTIVE_PS);

	rtw_coex_ips_notify(rtwdev, COEX_IPS_ENTER);

	rtw_core_stop(rtwdev);

	return 0;
}