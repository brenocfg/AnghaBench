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
struct uart_port {int flags; int /*<<< orphan*/  mapbase; int /*<<< orphan*/ * membase; TYPE_1__* dev; } ;
struct sci_port {int /*<<< orphan*/  reg_size; } ;
struct TYPE_2__ {scalar_t__ of_node; } ;

/* Variables and functions */
 int UPF_IOREMAP ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sci_port* to_sci_port (struct uart_port*) ; 

__attribute__((used)) static void sci_release_port(struct uart_port *port)
{
	struct sci_port *sport = to_sci_port(port);

	if (port->dev->of_node || (port->flags & UPF_IOREMAP)) {
		iounmap(port->membase);
		port->membase = NULL;
	}

	release_mem_region(port->mapbase, sport->reg_size);
}