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
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_is_assoc (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_phy_cck_pd_lv_link (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_phy_cck_pd_lv_unlink (struct rtw_dev*) ; 

__attribute__((used)) static u8 rtw_phy_cck_pd_lv(struct rtw_dev *rtwdev)
{
	if (!rtw_is_assoc(rtwdev))
		return rtw_phy_cck_pd_lv_unlink(rtwdev);
	else
		return rtw_phy_cck_pd_lv_link(rtwdev);
}