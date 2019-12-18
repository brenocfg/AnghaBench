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
typedef  int /*<<< orphan*/  u16 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int __ffs (int) ; 
 int /*<<< orphan*/  ltecoex_reg_write (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int rtw_coex_read_indirect_reg (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 

void rtw_coex_write_indirect_reg(struct rtw_dev *rtwdev, u16 addr,
				 u32 mask, u32 val)
{
	u32 shift = __ffs(mask);
	u32 tmp;

	tmp = rtw_coex_read_indirect_reg(rtwdev, addr);
	tmp = (tmp & (~mask)) | ((val << shift) & mask);

	if (!ltecoex_reg_write(rtwdev, addr, tmp))
		rtw_err(rtwdev, "failed to write indirect register\n");
}