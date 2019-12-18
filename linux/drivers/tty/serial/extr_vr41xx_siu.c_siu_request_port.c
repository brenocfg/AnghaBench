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
struct uart_port {int flags; int /*<<< orphan*/ * membase; int /*<<< orphan*/  mapbase; } ;
struct resource {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int UPF_IOREMAP ; 
 int /*<<< orphan*/ * ioremap (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  release_resource (struct resource*) ; 
 struct resource* request_mem_region (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long siu_port_size (struct uart_port*) ; 
 int /*<<< orphan*/  siu_type_name (struct uart_port*) ; 

__attribute__((used)) static int siu_request_port(struct uart_port *port)
{
	unsigned long size;
	struct resource *res;

	size = siu_port_size(port);
	res = request_mem_region(port->mapbase, size, siu_type_name(port));
	if (res == NULL)
		return -EBUSY;

	if (port->flags & UPF_IOREMAP) {
		port->membase = ioremap(port->mapbase, size);
		if (port->membase == NULL) {
			release_resource(res);
			return -ENOMEM;
		}
	}

	return 0;
}