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
 int /*<<< orphan*/  early_serial_base ; 
 int /*<<< orphan*/  parse_console_uart8250 () ; 
 int /*<<< orphan*/  parse_earlyprintk () ; 

void console_init(void)
{
	parse_earlyprintk();

	if (!early_serial_base)
		parse_console_uart8250();
}