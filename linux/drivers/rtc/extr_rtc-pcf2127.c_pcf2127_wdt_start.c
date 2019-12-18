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
 int pcf2127_wdt_ping (struct watchdog_device*) ; 

__attribute__((used)) static int pcf2127_wdt_start(struct watchdog_device *wdd)
{
	return pcf2127_wdt_ping(wdd);
}