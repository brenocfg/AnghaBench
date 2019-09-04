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
struct console {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amiga_serial_putc (char) ; 

__attribute__((used)) static void amiga_serial_console_write(struct console *co, const char *s,
				       unsigned int count)
{
	while (count--) {
		if (*s == '\n')
			amiga_serial_putc('\r');
		amiga_serial_putc(*s++);
	}
}