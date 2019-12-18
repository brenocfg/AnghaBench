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
typedef  size_t u32 ;
struct rtw_dev {int dummy; } ;
struct rtw_backup_info {int len; size_t reg; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_read32 (struct rtw_dev*,size_t) ; 

__attribute__((used)) static void
rtw8822c_dpk_backup_registers(struct rtw_dev *rtwdev, u32 *reg,
			      u32 reg_num, struct rtw_backup_info *bckp)
{
	u32 i;

	for (i = 0; i < reg_num; i++) {
		bckp[i].len = 4;
		bckp[i].reg = reg[i];
		bckp[i].val = rtw_read32(rtwdev, reg[i]);
	}
}