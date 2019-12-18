#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct rtw_dev {TYPE_1__* chip; } ;
struct TYPE_2__ {scalar_t__ is_pwr_by_rate_dec; } ;

/* Variables and functions */
 int bcd_to_dec_pwr_by_rate (int,int) ; 

__attribute__((used)) static u8 tbl_to_dec_pwr_by_rate(struct rtw_dev *rtwdev, u32 hex, u8 i)
{
	if (rtwdev->chip->is_pwr_by_rate_dec)
		return bcd_to_dec_pwr_by_rate(hex, i);

	return (hex >> (i * 8)) & 0xFF;
}