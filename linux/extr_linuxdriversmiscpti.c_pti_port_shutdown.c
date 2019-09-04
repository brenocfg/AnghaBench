#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty_port {TYPE_1__* tty; } ;
struct TYPE_2__ {scalar_t__ index; } ;

/* Variables and functions */
 scalar_t__ PTITTY_MINOR_START ; 
 int /*<<< orphan*/  console_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pti_console ; 

__attribute__((used)) static void pti_port_shutdown(struct tty_port *port)
{
	if (port->tty->index == PTITTY_MINOR_START)
		console_stop(&pti_console);
}