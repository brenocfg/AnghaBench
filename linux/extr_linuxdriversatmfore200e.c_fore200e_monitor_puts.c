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
struct fore200e {int dummy; } ;

/* Variables and functions */
 scalar_t__ fore200e_monitor_getc (struct fore200e*) ; 
 int /*<<< orphan*/  fore200e_monitor_putc (struct fore200e*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fore200e_monitor_puts(struct fore200e *fore200e, char *str)
{
    while (*str) {

	/* the i960 monitor doesn't accept any new character if it has something to say */
	while (fore200e_monitor_getc(fore200e) >= 0);
	
	fore200e_monitor_putc(fore200e, *str++);
    }

    while (fore200e_monitor_getc(fore200e) >= 0);
}