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
struct watchdog_device {int timeout; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ jiffies ; 
 scalar_t__ next_heartbeat ; 

__attribute__((used)) static int wdt_ping(struct watchdog_device *wdd)
{
	/* calculate when the next userspace timeout will be */
	next_heartbeat = jiffies + wdd->timeout * HZ;
	return 0;
}