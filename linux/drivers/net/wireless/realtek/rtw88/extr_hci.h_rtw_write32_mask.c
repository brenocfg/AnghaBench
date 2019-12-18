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
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int __ffs (int) ; 
 int rtw_read32 (struct rtw_dev*,int) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int,int) ; 

__attribute__((used)) static inline void
rtw_write32_mask(struct rtw_dev *rtwdev, u32 addr, u32 mask, u32 data)
{
	u32 shift = __ffs(mask);
	u32 orig;
	u32 set;

	WARN(addr & 0x3, "should be 4-byte aligned, addr = 0x%08x\n", addr);

	orig = rtw_read32(rtwdev, addr);
	set = (orig & ~mask) | ((data << shift) & mask);
	rtw_write32(rtwdev, addr, set);
}