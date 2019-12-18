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
struct watchdog_device {TYPE_1__* gov; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  pretimeout_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,char*) ; 

int watchdog_pretimeout_governor_get(struct watchdog_device *wdd, char *buf)
{
	int count = 0;

	spin_lock_irq(&pretimeout_lock);
	if (wdd->gov)
		count = sprintf(buf, "%s\n", wdd->gov->name);
	spin_unlock_irq(&pretimeout_lock);

	return count;
}