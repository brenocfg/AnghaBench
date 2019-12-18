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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 unsigned long SYS_HALT ; 
 unsigned long SYS_POWER_OFF ; 
 int /*<<< orphan*/  it8712f_wdt_disable () ; 
 int /*<<< orphan*/  nowayout ; 

__attribute__((used)) static int it8712f_wdt_notify(struct notifier_block *this,
		    unsigned long code, void *unused)
{
	if (code == SYS_HALT || code == SYS_POWER_OFF)
		if (!nowayout)
			it8712f_wdt_disable();

	return NOTIFY_DONE;
}