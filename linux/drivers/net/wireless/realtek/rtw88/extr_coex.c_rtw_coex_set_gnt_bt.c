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

/* Variables and functions */
 int /*<<< orphan*/  rtw_coex_write_indirect_reg (struct rtw_dev*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw_coex_set_gnt_bt(struct rtw_dev *rtwdev, u8 state)
{
	rtw_coex_write_indirect_reg(rtwdev, 0x38, 0xc000, state);
	rtw_coex_write_indirect_reg(rtwdev, 0x38, 0x0c00, state);
}