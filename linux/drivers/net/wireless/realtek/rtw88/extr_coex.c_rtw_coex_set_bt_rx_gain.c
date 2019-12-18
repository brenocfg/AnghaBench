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
typedef  scalar_t__ u8 ;
struct rtw_coex_dm {scalar_t__ cur_bt_lna_lvl; } ;
struct rtw_coex {struct rtw_coex_dm dm; } ;
struct rtw_dev {struct rtw_coex coex; } ;

/* Variables and functions */
 int /*<<< orphan*/  COEX_SCBD_RXGAIN ; 
 int /*<<< orphan*/  rtw_coex_set_lna_constrain_level (struct rtw_dev*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_coex_write_scbd (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtw_coex_set_bt_rx_gain(struct rtw_dev *rtwdev, u8 bt_lna_lvl)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_dm *coex_dm = &coex->dm;

	if (bt_lna_lvl == coex_dm->cur_bt_lna_lvl)
		return;

	coex_dm->cur_bt_lna_lvl = bt_lna_lvl;

	/* notify BT rx gain table changed */
	if (bt_lna_lvl < 7) {
		rtw_coex_set_lna_constrain_level(rtwdev, bt_lna_lvl);
		rtw_coex_write_scbd(rtwdev, COEX_SCBD_RXGAIN, true);
	} else {
		rtw_coex_write_scbd(rtwdev, COEX_SCBD_RXGAIN, false);
	}
}