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
struct rtw_dpk_info {int gnt_value; int /*<<< orphan*/  gnt_control; } ;
struct TYPE_2__ {struct rtw_dpk_info dpk_info; } ;
struct rtw_dev {TYPE_1__ dm_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  MASKBYTE1 ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int rtw_coex_read_indirect_reg (struct rtw_dev*,int) ; 
 int /*<<< orphan*/  rtw_coex_write_indirect_reg (struct rtw_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_read32 (struct rtw_dev*,int) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtw8822c_dpk_set_gnt_wl(struct rtw_dev *rtwdev, bool is_before_k)
{
	struct rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;

	if (is_before_k) {
		dpk_info->gnt_control = rtw_read32(rtwdev, 0x70);
		dpk_info->gnt_value = rtw_coex_read_indirect_reg(rtwdev, 0x38);
		rtw_write32_mask(rtwdev, 0x70, BIT(26), 0x1);
		rtw_coex_write_indirect_reg(rtwdev, 0x38, MASKBYTE1, 0x77);
	} else {
		rtw_coex_write_indirect_reg(rtwdev, 0x38, MASKDWORD,
					    dpk_info->gnt_value);
		rtw_write32(rtwdev, 0x70, dpk_info->gnt_control);
	}
}