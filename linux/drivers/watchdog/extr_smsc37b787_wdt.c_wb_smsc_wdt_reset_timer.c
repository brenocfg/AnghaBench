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
 int /*<<< orphan*/  IODEV_NO ; 
 int /*<<< orphan*/  close_io_config () ; 
 int /*<<< orphan*/  io_lock ; 
 int /*<<< orphan*/  open_io_config () ; 
 int /*<<< orphan*/  select_io_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  wdt_timeout_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdt_timer_conf (int) ; 

__attribute__((used)) static void wb_smsc_wdt_reset_timer(void)
{
	spin_lock(&io_lock);
	open_io_config();
	select_io_device(IODEV_NO);

	/* reset the timer */
	wdt_timeout_value(timeout);
	wdt_timer_conf(0x08);

	close_io_config();
	spin_unlock(&io_lock);
}