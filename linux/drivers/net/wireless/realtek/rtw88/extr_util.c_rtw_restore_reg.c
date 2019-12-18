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
typedef  int /*<<< orphan*/  u16 ;
struct rtw_dev {int dummy; } ;
struct rtw_backup_info {int len; int reg; int val; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_write16 (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int,int) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,int,int) ; 

void rtw_restore_reg(struct rtw_dev *rtwdev,
		     struct rtw_backup_info *bckp, u32 num)
{
	u8 len;
	u32 reg;
	u32 val;
	int i;

	for (i = 0; i < num; i++, bckp++) {
		len = bckp->len;
		reg = bckp->reg;
		val = bckp->val;

		switch (len) {
		case 1:
			rtw_write8(rtwdev, reg, (u8)val);
			break;
		case 2:
			rtw_write16(rtwdev, reg, (u16)val);
			break;
		case 4:
			rtw_write32(rtwdev, reg, (u32)val);
			break;
		default:
			break;
		}
	}
}