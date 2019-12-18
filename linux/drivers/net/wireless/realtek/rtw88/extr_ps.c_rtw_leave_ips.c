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
 int /*<<< orphan*/  COEX_IPS_LEAVE ; 
 int /*<<< orphan*/  rtw_coex_ips_notify (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 
 int rtw_ips_pwr_up (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_iterate_vifs_atomic (struct rtw_dev*,int /*<<< orphan*/ ,struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_restore_port_cfg_iter ; 

int rtw_leave_ips(struct rtw_dev *rtwdev)
{
	int ret;

	ret = rtw_ips_pwr_up(rtwdev);
	if (ret) {
		rtw_err(rtwdev, "failed to leave ips state\n");
		return ret;
	}

	rtw_iterate_vifs_atomic(rtwdev, rtw_restore_port_cfg_iter, rtwdev);

	rtw_coex_ips_notify(rtwdev, COEX_IPS_LEAVE);

	return 0;
}