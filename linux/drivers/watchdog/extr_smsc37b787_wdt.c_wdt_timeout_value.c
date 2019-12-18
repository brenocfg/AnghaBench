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
 int /*<<< orphan*/  write_io_cr (int,unsigned char) ; 

__attribute__((used)) static inline void wdt_timeout_value(unsigned char new_timeout)
{
	/* -- Watchdog Timer Time-out Value --
	 * Bit 0-7 Binary coded units (0=Disabled, 1..255)
	 */
	write_io_cr(0xF2, new_timeout);
}