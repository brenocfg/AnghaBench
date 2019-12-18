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
struct serio {struct q40kbd* port_data; } ;
struct q40kbd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  q40kbd_flush (struct q40kbd*) ; 
 int /*<<< orphan*/  q40kbd_stop () ; 

__attribute__((used)) static void q40kbd_close(struct serio *port)
{
	struct q40kbd *q40kbd = port->port_data;

	q40kbd_stop();
	q40kbd_flush(q40kbd);
}