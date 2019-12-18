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
struct console {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  goldfish_tty_do_write (int /*<<< orphan*/ ,char const*,unsigned int) ; 

__attribute__((used)) static void goldfish_tty_console_write(struct console *co, const char *b,
								unsigned count)
{
	goldfish_tty_do_write(co->index, b, count);
}