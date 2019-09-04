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
struct line {int dummy; } ;
struct console {size_t index; } ;

/* Variables and functions */
 int console_open_chan (struct line*,struct console*) ; 
 struct line* serial_lines ; 

__attribute__((used)) static int ssl_console_setup(struct console *co, char *options)
{
	struct line *line = &serial_lines[co->index];

	return console_open_chan(line, co);
}