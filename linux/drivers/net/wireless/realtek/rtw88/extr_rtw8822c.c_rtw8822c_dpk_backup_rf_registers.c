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

/* Variables and functions */
 size_t DPK_RF_REG_NUM ; 
 int /*<<< orphan*/  RFREG_MASK ; 
 size_t RF_PATH_A ; 
 size_t RF_PATH_B ; 
 size_t rtw_read_rf (struct rtw_dev*,size_t,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw8822c_dpk_backup_rf_registers(struct rtw_dev *rtwdev,
					     u32 *rf_reg,
					     u32 rf_reg_bak[][2])
{
	u32 i;

	for (i = 0; i < DPK_RF_REG_NUM; i++) {
		rf_reg_bak[i][RF_PATH_A] = rtw_read_rf(rtwdev, RF_PATH_A,
						       rf_reg[i], RFREG_MASK);
		rf_reg_bak[i][RF_PATH_B] = rtw_read_rf(rtwdev, RF_PATH_B,
						       rf_reg[i], RFREG_MASK);
	}
}