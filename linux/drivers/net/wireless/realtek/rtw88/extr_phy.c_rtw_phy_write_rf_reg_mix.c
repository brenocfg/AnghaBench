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
typedef  enum rtw_rf_path { ____Placeholder_rtw_rf_path } rtw_rf_path ;

/* Variables and functions */
 int rtw_phy_write_rf_reg (struct rtw_dev*,int,int,int,int) ; 
 int rtw_phy_write_rf_reg_sipi (struct rtw_dev*,int,int,int,int) ; 

bool rtw_phy_write_rf_reg_mix(struct rtw_dev *rtwdev, enum rtw_rf_path rf_path,
			      u32 addr, u32 mask, u32 data)
{
	if (addr != 0x00)
		return rtw_phy_write_rf_reg(rtwdev, rf_path, addr, mask, data);

	return rtw_phy_write_rf_reg_sipi(rtwdev, rf_path, addr, mask, data);
}