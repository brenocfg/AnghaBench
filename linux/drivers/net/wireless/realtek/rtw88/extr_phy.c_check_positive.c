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
struct rtw_phy_cond {scalar_t__ cut; scalar_t__ pkg; scalar_t__ intf; scalar_t__ rfe; } ;
struct rtw_hal {struct rtw_phy_cond phy_cond; } ;
struct rtw_dev {struct rtw_hal hal; } ;

/* Variables and functions */

__attribute__((used)) static bool check_positive(struct rtw_dev *rtwdev, struct rtw_phy_cond cond)
{
	struct rtw_hal *hal = &rtwdev->hal;
	struct rtw_phy_cond drv_cond = hal->phy_cond;

	if (cond.cut && cond.cut != drv_cond.cut)
		return false;

	if (cond.pkg && cond.pkg != drv_cond.pkg)
		return false;

	if (cond.intf && cond.intf != drv_cond.intf)
		return false;

	if (cond.rfe != drv_cond.rfe)
		return false;

	return true;
}