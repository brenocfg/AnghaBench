#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int last_box_num; int /*<<< orphan*/  lock; } ;
struct rtw_dev {TYPE_1__ h2c; } ;

/* Variables and functions */
 int REG_HMEBOX0 ; 
 int REG_HMEBOX0_EX ; 
 int REG_HMEBOX1 ; 
 int REG_HMEBOX1_EX ; 
 int REG_HMEBOX2 ; 
 int REG_HMEBOX2_EX ; 
 int REG_HMEBOX3 ; 
 int REG_HMEBOX3_EX ; 
 int /*<<< orphan*/  REG_HMETFR ; 
 int /*<<< orphan*/  RTW_DBG_FW ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  rtw_dbg (struct rtw_dev*,int /*<<< orphan*/ ,char*,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 
 int rtw_read8 (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtw_fw_send_h2c_command(struct rtw_dev *rtwdev,
				    u8 *h2c)
{
	u8 box;
	u8 box_state;
	u32 box_reg, box_ex_reg;
	u32 h2c_wait;
	int idx;

	rtw_dbg(rtwdev, RTW_DBG_FW,
		"send H2C content %02x%02x%02x%02x %02x%02x%02x%02x\n",
		h2c[3], h2c[2], h2c[1], h2c[0],
		h2c[7], h2c[6], h2c[5], h2c[4]);

	spin_lock(&rtwdev->h2c.lock);

	box = rtwdev->h2c.last_box_num;
	switch (box) {
	case 0:
		box_reg = REG_HMEBOX0;
		box_ex_reg = REG_HMEBOX0_EX;
		break;
	case 1:
		box_reg = REG_HMEBOX1;
		box_ex_reg = REG_HMEBOX1_EX;
		break;
	case 2:
		box_reg = REG_HMEBOX2;
		box_ex_reg = REG_HMEBOX2_EX;
		break;
	case 3:
		box_reg = REG_HMEBOX3;
		box_ex_reg = REG_HMEBOX3_EX;
		break;
	default:
		WARN(1, "invalid h2c mail box number\n");
		goto out;
	}

	h2c_wait = 20;
	do {
		box_state = rtw_read8(rtwdev, REG_HMETFR);
	} while ((box_state >> box) & 0x1 && --h2c_wait > 0);

	if (!h2c_wait) {
		rtw_err(rtwdev, "failed to send h2c command\n");
		goto out;
	}

	for (idx = 0; idx < 4; idx++)
		rtw_write8(rtwdev, box_reg + idx, h2c[idx]);
	for (idx = 0; idx < 4; idx++)
		rtw_write8(rtwdev, box_ex_reg + idx, h2c[idx + 4]);

	if (++rtwdev->h2c.last_box_num >= 4)
		rtwdev->h2c.last_box_num = 0;

out:
	spin_unlock(&rtwdev->h2c.lock);
}