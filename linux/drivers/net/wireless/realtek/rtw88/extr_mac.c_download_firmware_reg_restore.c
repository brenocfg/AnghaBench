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
struct rtw_backup_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_restore_reg (struct rtw_dev*,struct rtw_backup_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void download_firmware_reg_restore(struct rtw_dev *rtwdev,
					  struct rtw_backup_info *bckp,
					  u8 bckp_num)
{
	rtw_restore_reg(rtwdev, bckp, bckp_num);
}