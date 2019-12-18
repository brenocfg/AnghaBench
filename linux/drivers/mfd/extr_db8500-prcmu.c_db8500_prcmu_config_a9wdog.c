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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  A9WDOG_AUTO_OFF_DIS ; 
 int /*<<< orphan*/  A9WDOG_AUTO_OFF_EN ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  MB4H_A9WDOG_CONF ; 
 int prcmu_a9wdog (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int db8500_prcmu_config_a9wdog(u8 num, bool sleep_auto_off)
{
	BUG_ON(num == 0 || num > 0xf);
	return prcmu_a9wdog(MB4H_A9WDOG_CONF, num, 0, 0,
			    sleep_auto_off ? A9WDOG_AUTO_OFF_EN :
			    A9WDOG_AUTO_OFF_DIS);
}