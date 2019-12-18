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
struct adapter {int bCardDisableWOHSM; int net_closed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
 int /*<<< orphan*/  rtw_ips_dev_unload (struct adapter*) ; 

void rtw_ips_pwr_down(struct adapter *padapter)
{
	DBG_871X("===> rtw_ips_pwr_down...................\n");

	padapter->bCardDisableWOHSM = true;
	padapter->net_closed = true;

	rtw_ips_dev_unload(padapter);
	padapter->bCardDisableWOHSM = false;
	DBG_871X("<=== rtw_ips_pwr_down.....................\n");
}