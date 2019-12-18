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
 scalar_t__ UNIT_SECOND ; 
 int /*<<< orphan*/  close_io_config () ; 
 int /*<<< orphan*/  gpio_bit12 (int) ; 
 int /*<<< orphan*/  gpio_bit13 (int) ; 
 int /*<<< orphan*/  io_lock ; 
 int /*<<< orphan*/  open_io_config () ; 
 int read_io_cr (int) ; 
 int /*<<< orphan*/  select_io_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unit ; 
 int /*<<< orphan*/  wdt_timeout_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdt_timer_conf (int) ; 
 int /*<<< orphan*/  wdt_timer_ctrl (int) ; 
 int /*<<< orphan*/  wdt_timer_units (unsigned char) ; 

__attribute__((used)) static void wb_smsc_wdt_initialize(void)
{
	unsigned char old;

	spin_lock(&io_lock);
	open_io_config();
	select_io_device(IODEV_NO);

	/* enable the watchdog */
	gpio_bit13(0x08);  /* Select pin 80 = LED not GPIO */
	gpio_bit12(0x0A);  /* Set pin 79 = WDT not
			      GPIO/Output/Polarity=Invert */
	/* disable the timeout */
	wdt_timeout_value(0);

	/* reset control register */
	wdt_timer_ctrl(0x00);

	/* reset configuration register */
	wdt_timer_conf(0x00);

	/* read old (timer units) register */
	old = read_io_cr(0xF1) & 0x7F;
	if (unit == UNIT_SECOND)
		old |= 0x80;	/* set to seconds */

	/* set the watchdog timer units */
	wdt_timer_units(old);

	close_io_config();
	spin_unlock(&io_lock);
}