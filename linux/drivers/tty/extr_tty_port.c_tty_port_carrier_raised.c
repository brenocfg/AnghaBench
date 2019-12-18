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
struct tty_port {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* carrier_raised ) (struct tty_port*) ;} ;

/* Variables and functions */
 int stub1 (struct tty_port*) ; 

int tty_port_carrier_raised(struct tty_port *port)
{
	if (port->ops->carrier_raised == NULL)
		return 1;
	return port->ops->carrier_raised(port);
}