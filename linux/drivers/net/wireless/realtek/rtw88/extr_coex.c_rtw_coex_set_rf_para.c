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
typedef  int u8 ;
struct rtw_coex_stat {int wl_noisy_level; } ;
struct rtw_coex {scalar_t__ freerun; struct rtw_coex_stat stat; } ;
struct rtw_dev {struct rtw_coex coex; } ;
struct coex_rf_para {int /*<<< orphan*/  bt_lna_lvl; int /*<<< orphan*/  wl_low_gain_en; scalar_t__ bt_pwr_dec_lvl; int /*<<< orphan*/  wl_pwr_dec_lvl; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_coex_set_bt_rx_gain (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_set_bt_tx_power (struct rtw_dev*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_coex_set_wl_rx_gain (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_set_wl_tx_power (struct rtw_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw_coex_set_rf_para(struct rtw_dev *rtwdev,
				 struct coex_rf_para para)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;
	u8 offset = 0;

	if (coex->freerun && coex_stat->wl_noisy_level <= 1)
		offset = 3;

	rtw_coex_set_wl_tx_power(rtwdev, para.wl_pwr_dec_lvl);
	rtw_coex_set_bt_tx_power(rtwdev, para.bt_pwr_dec_lvl + offset);
	rtw_coex_set_wl_rx_gain(rtwdev, para.wl_low_gain_en);
	rtw_coex_set_bt_rx_gain(rtwdev, para.bt_lna_lvl);
}