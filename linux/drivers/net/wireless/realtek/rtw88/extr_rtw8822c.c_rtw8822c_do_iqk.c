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
struct rtw_iqk_para {int clear; int /*<<< orphan*/  member_0; } ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_IQKSTAT ; 
 int /*<<< orphan*/  REG_RPT_CIP ; 
 int /*<<< orphan*/  RTW_DBG_RFK ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rtw_dbg (struct rtw_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rtw_fw_do_iqk (struct rtw_dev*,struct rtw_iqk_para*) ; 
 int rtw_read8 (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtw8822c_do_iqk(struct rtw_dev *rtwdev)
{
	struct rtw_iqk_para para = {0};
	u8 iqk_chk;
	int counter;

	para.clear = 1;
	rtw_fw_do_iqk(rtwdev, &para);

	for (counter = 0; counter < 300; counter++) {
		iqk_chk = rtw_read8(rtwdev, REG_RPT_CIP);
		if (iqk_chk == 0xaa)
			break;
		msleep(20);
	}
	rtw_write8(rtwdev, REG_IQKSTAT, 0x0);

	rtw_dbg(rtwdev, RTW_DBG_RFK, "iqk counter=%d\n", counter);
}