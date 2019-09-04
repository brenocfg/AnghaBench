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
 int /*<<< orphan*/  error_putstr (char*) ; 
 int /*<<< orphan*/  warn (char*) ; 

void error(char *m)
{
	warn(m);
	error_putstr(" -- System halted");

	while (1)
		asm("hlt");
}