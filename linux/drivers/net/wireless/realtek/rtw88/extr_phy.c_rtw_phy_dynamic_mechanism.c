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
 int /*<<< orphan*/  rtw_phy_cck_pd (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_phy_dig (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_phy_dpk_track (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_phy_ra_info_update (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_phy_statistics (struct rtw_dev*) ; 

void rtw_phy_dynamic_mechanism(struct rtw_dev *rtwdev)
{
	/* for further calculation */
	rtw_phy_statistics(rtwdev);
	rtw_phy_dig(rtwdev);
	rtw_phy_cck_pd(rtwdev);
	rtw_phy_ra_info_update(rtwdev);
	rtw_phy_dpk_track(rtwdev);
}