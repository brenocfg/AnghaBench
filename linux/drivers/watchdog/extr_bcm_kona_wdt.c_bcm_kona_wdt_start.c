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
struct watchdog_device {int dummy; } ;

/* Variables and functions */
 int SECWDOG_EN_MASK ; 
 int SECWDOG_SRSTEN_MASK ; 
 int bcm_kona_wdt_set_timeout_reg (struct watchdog_device*,int) ; 

__attribute__((used)) static int bcm_kona_wdt_start(struct watchdog_device *wdog)
{
	return bcm_kona_wdt_set_timeout_reg(wdog,
					SECWDOG_EN_MASK | SECWDOG_SRSTEN_MASK);
}