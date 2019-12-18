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
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int rtw_read32_mask (struct rtw_dev*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

bool check_hw_ready(struct rtw_dev *rtwdev, u32 addr, u32 mask, u32 target)
{
	u32 cnt;

	for (cnt = 0; cnt < 1000; cnt++) {
		if (rtw_read32_mask(rtwdev, addr, mask) == target)
			return true;

		udelay(10);
	}

	return false;
}