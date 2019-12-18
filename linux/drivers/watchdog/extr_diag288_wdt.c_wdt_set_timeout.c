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
struct watchdog_device {unsigned int timeout; } ;

/* Variables and functions */
 int wdt_ping (struct watchdog_device*) ; 

__attribute__((used)) static int wdt_set_timeout(struct watchdog_device * dev, unsigned int new_to)
{
	dev->timeout = new_to;
	return wdt_ping(dev);
}