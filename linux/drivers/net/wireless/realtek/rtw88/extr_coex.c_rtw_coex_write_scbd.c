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
typedef  int u16 ;
struct rtw_coex_stat {int score_board; } ;
struct rtw_coex {struct rtw_coex_stat stat; } ;
struct rtw_dev {struct rtw_coex coex; struct rtw_chip_info* chip; } ;
struct rtw_chip_info {int /*<<< orphan*/  new_scbd10_def; int /*<<< orphan*/  scbd_support; } ;

/* Variables and functions */
 int BIT_BT_INT_EN ; 
 int COEX_SCBD_FIX2M ; 
 int /*<<< orphan*/  REG_WIFI_BT_INFO ; 
 int /*<<< orphan*/  rtw_write16 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 

void rtw_coex_write_scbd(struct rtw_dev *rtwdev, u16 bitpos, bool set)
{
	struct rtw_chip_info *chip = rtwdev->chip;
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;
	u16 val = 0x2;

	if (!chip->scbd_support)
		return;

	val |= coex_stat->score_board;

	/* for 8822b, scbd[10] is CQDDR on
	 * for 8822c, scbd[10] is no fix 2M
	 */
	if (!chip->new_scbd10_def && (bitpos & COEX_SCBD_FIX2M)) {
		if (set)
			val &= ~COEX_SCBD_FIX2M;
		else
			val |= COEX_SCBD_FIX2M;
	} else {
		if (set)
			val |= bitpos;
		else
			val &= ~bitpos;
	}

	if (val != coex_stat->score_board) {
		coex_stat->score_board = val;
		val |= BIT_BT_INT_EN;
		rtw_write16(rtwdev, REG_WIFI_BT_INFO, val);
	}
}