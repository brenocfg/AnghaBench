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
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_MASK_EFUSE_BANK_SEL ; 
 int /*<<< orphan*/  REG_LDO_EFUSE_CTRL ; 
 int /*<<< orphan*/  RTW_EFUSE_BANK_WIFI ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void switch_efuse_bank(struct rtw_dev *rtwdev)
{
	rtw_write32_mask(rtwdev, REG_LDO_EFUSE_CTRL, BIT_MASK_EFUSE_BANK_SEL,
			 RTW_EFUSE_BANK_WIFI);
}