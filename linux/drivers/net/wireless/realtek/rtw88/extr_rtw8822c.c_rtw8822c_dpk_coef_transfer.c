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
typedef  int u32 ;
typedef  int u16 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASKHWORD ; 
 int /*<<< orphan*/  MASKLWORD ; 
 int /*<<< orphan*/  REG_STAT_RPT ; 
 int rtw_read32 (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_read32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 rtw8822c_dpk_coef_transfer(struct rtw_dev *rtwdev)
{
	u32 reg = 0;
	u16 coef_i = 0, coef_q = 0;

	reg = rtw_read32(rtwdev, REG_STAT_RPT);

	coef_i = (u16)rtw_read32_mask(rtwdev, REG_STAT_RPT, MASKHWORD) & 0x1fff;
	coef_q = (u16)rtw_read32_mask(rtwdev, REG_STAT_RPT, MASKLWORD) & 0x1fff;

	coef_q = ((0x2000 - coef_q) & 0x1fff) - 1;

	reg = (coef_i << 16) | coef_q;

	return reg;
}