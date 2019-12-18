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
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ caused_reboot; } ;

/* Variables and functions */
 int WDIOF_CARDRESET ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ watchdog ; 

__attribute__((used)) static int watchdog_get_status(void)
{
	int status = 0;

	mutex_lock(&watchdog.lock);
	status = (watchdog.caused_reboot) ? WDIOF_CARDRESET : 0;
	mutex_unlock(&watchdog.lock);

	return status;
}