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
 int EALREADY ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 
 int rtw_mac_init_system_cfg (struct rtw_dev*) ; 
 int rtw_mac_power_switch (struct rtw_dev*,int) ; 
 int rtw_mac_pre_system_cfg (struct rtw_dev*) ; 

int rtw_mac_power_on(struct rtw_dev *rtwdev)
{
	int ret = 0;

	ret = rtw_mac_pre_system_cfg(rtwdev);
	if (ret)
		goto err;

	ret = rtw_mac_power_switch(rtwdev, true);
	if (ret == -EALREADY) {
		rtw_mac_power_switch(rtwdev, false);
		ret = rtw_mac_power_switch(rtwdev, true);
		if (ret)
			goto err;
	} else if (ret) {
		goto err;
	}

	ret = rtw_mac_init_system_cfg(rtwdev);
	if (ret)
		goto err;

	return 0;

err:
	rtw_err(rtwdev, "mac power on failed");
	return ret;
}