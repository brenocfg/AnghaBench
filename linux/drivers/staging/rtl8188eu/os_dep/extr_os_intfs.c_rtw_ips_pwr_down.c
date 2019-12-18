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
struct adapter {int net_closed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_88E (char*,...) ; 
 int /*<<< orphan*/  LED_CTL_POWER_OFF ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  led_control_8188eu (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_ips_dev_unload (struct adapter*) ; 

void rtw_ips_pwr_down(struct adapter *padapter)
{
	unsigned long start_time = jiffies;

	DBG_88E("===> rtw_ips_pwr_down...................\n");

	padapter->net_closed = true;

	led_control_8188eu(padapter, LED_CTL_POWER_OFF);

	rtw_ips_dev_unload(padapter);
	DBG_88E("<=== rtw_ips_pwr_down..................... in %dms\n",
		jiffies_to_msecs(jiffies - start_time));
}