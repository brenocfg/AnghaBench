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
struct rtw_backup_info {size_t val; size_t reg; } ;

/* Variables and functions */
 size_t DACK_PATH_8822C ; 
 int /*<<< orphan*/  DACK_REG_8822C ; 
 size_t DACK_RF_8822C ; 
 int /*<<< orphan*/  RFREG_MASK ; 
 int /*<<< orphan*/  rtw_restore_reg (struct rtw_dev*,struct rtw_backup_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write_rf (struct rtw_dev*,size_t,size_t,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void rtw8822c_dac_restore_reg(struct rtw_dev *rtwdev,
				     struct rtw_backup_info *backup,
				     struct rtw_backup_info *backup_rf)
{
	u32 path, i;
	u32 val;
	u32 reg;

	rtw_restore_reg(rtwdev, backup, DACK_REG_8822C);

	for (path = 0; path < DACK_PATH_8822C; path++) {
		for (i = 0; i < DACK_RF_8822C; i++) {
			val = backup_rf[path * i + i].val;
			reg = backup_rf[path * i + i].reg;
			rtw_write_rf(rtwdev, path, reg, RFREG_MASK, val);
		}
	}
}