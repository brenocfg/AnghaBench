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
struct uart_amba_port {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct uart_amba_port**) ; 
 struct uart_amba_port** amba_ports ; 
 int /*<<< orphan*/  amba_reg ; 
 int /*<<< orphan*/  pl011_dma_remove (struct uart_amba_port*) ; 
 int /*<<< orphan*/  uart_unregister_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pl011_unregister_port(struct uart_amba_port *uap)
{
	int i;
	bool busy = false;

	for (i = 0; i < ARRAY_SIZE(amba_ports); i++) {
		if (amba_ports[i] == uap)
			amba_ports[i] = NULL;
		else if (amba_ports[i])
			busy = true;
	}
	pl011_dma_remove(uap);
	if (!busy)
		uart_unregister_driver(&amba_reg);
}