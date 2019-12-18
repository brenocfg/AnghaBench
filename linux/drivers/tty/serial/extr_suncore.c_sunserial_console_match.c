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
struct uart_driver {struct console* cons; } ;
struct device_node {int dummy; } ;
struct console {int index; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_preferred_console (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  console_set_on_cmdline ; 
 struct device_node* of_console_device ; 
 char* of_console_options ; 

int sunserial_console_match(struct console *con, struct device_node *dp,
			    struct uart_driver *drv, int line, bool ignore_line)
{
	if (!con)
		return 0;

	drv->cons = con;

	if (of_console_device != dp)
		return 0;

	if (!ignore_line) {
		int off = 0;

		if (of_console_options &&
		    *of_console_options == 'b')
			off = 1;

		if ((line & 1) != off)
			return 0;
	}

	if (!console_set_on_cmdline) {
		con->index = line;
		add_preferred_console(con->name, line, NULL);
	}
	return 1;
}