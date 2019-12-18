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
 int /*<<< orphan*/  BIT_LTE_MUX_CTRL_PATH ; 
 int /*<<< orphan*/  REG_SYS_SDIO_CTRL ; 
 int /*<<< orphan*/  rtw_write32_clr (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32_set (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw_coex_coex_ctrl_owner(struct rtw_dev *rtwdev, bool wifi_control)
{
	if (wifi_control)
		rtw_write32_set(rtwdev, REG_SYS_SDIO_CTRL, BIT_LTE_MUX_CTRL_PATH);
	else
		rtw_write32_clr(rtwdev, REG_SYS_SDIO_CTRL, BIT_LTE_MUX_CTRL_PATH);
}