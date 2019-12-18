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
typedef  int u32 ;
struct rtw_coex_rfe {scalar_t__ wlg_at_btg; } ;
struct rtw_coex_stat {int bt_iqk_state; } ;
struct rtw_coex {struct rtw_coex_rfe rfe; struct rtw_coex_stat stat; } ;
struct rtw_dev {struct rtw_coex coex; struct rtw_chip_info* chip; } ;
struct rtw_chip_info {scalar_t__ scbd_support; } ;

/* Variables and functions */
 int BIT_WL_RFK ; 
 int COEX_MIN_DELAY ; 
 int COEX_RFK_TIMEOUT ; 
 int COEX_SCBD_BT_RFK ; 
 int /*<<< orphan*/  REG_ARFR4 ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int rtw_coex_read_scbd (struct rtw_dev*) ; 
 int rtw_read8 (struct rtw_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw_coex_check_rfk(struct rtw_dev *rtwdev)
{
	struct rtw_chip_info *chip = rtwdev->chip;
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;
	struct rtw_coex_rfe *coex_rfe = &coex->rfe;
	u8 cnt = 0;
	u32 wait_cnt;
	bool btk, wlk;

	if (coex_rfe->wlg_at_btg && chip->scbd_support &&
	    coex_stat->bt_iqk_state != 0xff) {
		wait_cnt = COEX_RFK_TIMEOUT / COEX_MIN_DELAY;
		do {
			/* BT RFK */
			btk = !!(rtw_coex_read_scbd(rtwdev) & COEX_SCBD_BT_RFK);

			/* WL RFK */
			wlk = !!(rtw_read8(rtwdev, REG_ARFR4) & BIT_WL_RFK);

			if (!btk && !wlk)
				break;

			mdelay(COEX_MIN_DELAY);
		} while (++cnt < wait_cnt);

		if (cnt >= wait_cnt)
			coex_stat->bt_iqk_state = 0xff;
	}
}