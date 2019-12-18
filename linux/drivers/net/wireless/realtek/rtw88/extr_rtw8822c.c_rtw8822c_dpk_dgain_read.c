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
typedef  scalar_t__ u16 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int BIT_SUBPAGE ; 
 int /*<<< orphan*/  GENMASK (int,int) ; 
 int /*<<< orphan*/  REG_NCTL0 ; 
 int /*<<< orphan*/  REG_RXSRAM_CTL ; 
 int /*<<< orphan*/  REG_STAT_RPT ; 
 scalar_t__ rtw_read32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static u16 rtw8822c_dpk_dgain_read(struct rtw_dev *rtwdev, u8 path)
{
	u16 dgain;

	rtw_write32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0xc);
	rtw_write32_mask(rtwdev, REG_RXSRAM_CTL, 0x00ff0000, 0x0);

	dgain = (u16)rtw_read32_mask(rtwdev, REG_STAT_RPT, GENMASK(27, 16));

	return dgain;
}