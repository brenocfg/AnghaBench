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
 int /*<<< orphan*/  DBG_88E (char*,...) ; 
 int /*<<< orphan*/  LED_CTL_NO_LINK ; 
 int ips_netdrv_open (struct adapter*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  led_control_8188eu (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_reset_drv_sw (struct adapter*) ; 

int rtw_ips_pwr_up(struct adapter *padapter)
{
	int result;
	unsigned long start_time = jiffies;

	DBG_88E("===>  rtw_ips_pwr_up..............\n");
	rtw_reset_drv_sw(padapter);

	result = ips_netdrv_open(padapter);

	led_control_8188eu(padapter, LED_CTL_NO_LINK);

	DBG_88E("<===  rtw_ips_pwr_up.............. in %dms\n",
		jiffies_to_msecs(jiffies - start_time));
	return result;
}