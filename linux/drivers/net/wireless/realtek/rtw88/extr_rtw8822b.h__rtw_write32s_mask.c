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
typedef  scalar_t__ u32 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void
_rtw_write32s_mask(struct rtw_dev *rtwdev, u32 addr, u32 mask, u32 data)
{
	/* 0xC00-0xCFF and 0xE00-0xEFF have the same layout */
	rtw_write32_mask(rtwdev, addr, mask, data);
	rtw_write32_mask(rtwdev, addr + 0x200, mask, data);
}