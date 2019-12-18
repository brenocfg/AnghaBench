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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
 int ips_netdrv_open (struct adapter*) ; 

int rtw_ips_pwr_up(struct adapter *padapter)
{
	int result;
	DBG_871X("===>  rtw_ips_pwr_up..............\n");

	result = ips_netdrv_open(padapter);

	DBG_871X("<===  rtw_ips_pwr_up..............\n");
	return result;
}