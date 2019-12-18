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
typedef  int u16 ;
struct sta_info {int mac_id; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_H2C_MEDIA_STATUS_RPT ; 
 int /*<<< orphan*/  HW_VAR_TX_RPT_MAX_MACID ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  search_max_mac_id (struct adapter*) ; 

void rtw_stassoc_hw_rpt(struct adapter *adapter, struct sta_info *psta)
{
	u16 media_status;
	u8 macid;

	if (!psta)
		return;

	macid = search_max_mac_id(adapter);
	rtw_hal_set_hwreg(adapter, HW_VAR_TX_RPT_MAX_MACID, (u8 *)&macid);
	media_status = (psta->mac_id<<8)|1; /*   MACID|OPMODE:1 connect */
	rtw_hal_set_hwreg(adapter, HW_VAR_H2C_MEDIA_STATUS_RPT, (u8 *)&media_status);
}