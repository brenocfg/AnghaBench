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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int rtw_read16 (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write16 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void rtw_write16_set(struct rtw_dev *rtwdev, u32 addr, u16 bit)
{
	u16 val;

	val = rtw_read16(rtwdev, addr);
	rtw_write16(rtwdev, addr, val | bit);
}