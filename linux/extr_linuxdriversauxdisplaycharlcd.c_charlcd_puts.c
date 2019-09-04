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
struct charlcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  charlcd_write_char (struct charlcd*,char const) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  schedule () ; 
 int strlen (char const*) ; 

__attribute__((used)) static void charlcd_puts(struct charlcd *lcd, const char *s)
{
	const char *tmp = s;
	int count = strlen(s);

	for (; count-- > 0; tmp++) {
		if (!in_interrupt() && (((count + 1) & 0x1f) == 0))
			/*
			 * let's be a little nice with other processes
			 * that need some CPU
			 */
			schedule();

		charlcd_write_char(lcd, *tmp);
	}
}