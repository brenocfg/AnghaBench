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
 unsigned char read_io_cr (int) ; 
 int /*<<< orphan*/  select_io_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned char wb_smsc_wdt_get_timeout(void)
{
	unsigned char set_timeout;

	spin_lock(&io_lock);
	open_io_config();
	select_io_device(IODEV_NO);
	set_timeout = read_io_cr(0xF2);
	close_io_config();
	spin_unlock(&io_lock);

	return set_timeout;
}