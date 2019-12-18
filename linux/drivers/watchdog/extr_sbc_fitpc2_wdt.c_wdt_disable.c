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

/* Variables and functions */
 int /*<<< orphan*/  IFACE_ON_COMMAND ; 
 int /*<<< orphan*/  REBOOT_COMMAND ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_lock ; 
 int /*<<< orphan*/  wdt_send_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wdt_disable(void)
{
	mutex_lock(&wdt_lock);
	wdt_send_data(IFACE_ON_COMMAND, 0);
	wdt_send_data(REBOOT_COMMAND, 0);
	mutex_unlock(&wdt_lock);
}