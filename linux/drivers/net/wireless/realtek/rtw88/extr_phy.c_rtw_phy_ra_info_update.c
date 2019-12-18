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
struct rtw_dev {int watch_dog_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_iterate_stas_atomic (struct rtw_dev*,int /*<<< orphan*/ ,struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_phy_ra_info_update_iter ; 

__attribute__((used)) static void rtw_phy_ra_info_update(struct rtw_dev *rtwdev)
{
	if (rtwdev->watch_dog_cnt & 0x3)
		return;

	rtw_iterate_stas_atomic(rtwdev, rtw_phy_ra_info_update_iter, rtwdev);
}