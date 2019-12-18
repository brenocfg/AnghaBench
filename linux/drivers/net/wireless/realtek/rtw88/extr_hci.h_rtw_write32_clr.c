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
 int rtw_read32 (struct rtw_dev*,int) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int,int) ; 

__attribute__((used)) static inline void rtw_write32_clr(struct rtw_dev *rtwdev, u32 addr, u32 bit)
{
	u32 val;

	val = rtw_read32(rtwdev, addr);
	rtw_write32(rtwdev, addr, val & ~bit);
}