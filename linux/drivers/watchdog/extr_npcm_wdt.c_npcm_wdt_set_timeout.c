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
 int /*<<< orphan*/  npcm_wdt_start (struct watchdog_device*) ; 
 scalar_t__ watchdog_active (struct watchdog_device*) ; 

__attribute__((used)) static int npcm_wdt_set_timeout(struct watchdog_device *wdd,
				unsigned int timeout)
{
	if (timeout < 2)
		wdd->timeout = 1;
	else if (timeout < 3)
	      wdd->timeout = 2;
	else if (timeout < 6)
	      wdd->timeout = 5;
	else if (timeout < 11)
	      wdd->timeout = 10;
	else if (timeout < 22)
	      wdd->timeout = 21;
	else if (timeout < 44)
	      wdd->timeout = 43;
	else if (timeout < 87)
	      wdd->timeout = 86;
	else if (timeout < 173)
	      wdd->timeout = 172;
	else if (timeout < 688)
	      wdd->timeout = 687;
	else
	      wdd->timeout = 2750;

	if (watchdog_active(wdd))
		npcm_wdt_start(wdd);

	return 0;
}