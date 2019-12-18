#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ next_heartbeat; } ;

/* Variables and functions */
 scalar_t__ DEBUG ; 
 int HZ ; 
 scalar_t__ debug ; 
 int heartbeat ; 
 scalar_t__ jiffies ; 
 TYPE_1__ pcwd_private ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int pcwd_keepalive(void)
{
	/* user land ping */
	pcwd_private.next_heartbeat = jiffies + (heartbeat * HZ);

	if (debug >= DEBUG)
		pr_debug("Watchdog keepalive signal send\n");

	return 0;
}