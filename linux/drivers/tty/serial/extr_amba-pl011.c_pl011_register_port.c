#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct uart_amba_port {TYPE_3__ port; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_ICR ; 
 int /*<<< orphan*/  REG_IMSC ; 
 TYPE_1__ amba_reg ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pl011_unregister_port (struct uart_amba_port*) ; 
 int /*<<< orphan*/  pl011_write (int,struct uart_amba_port*,int /*<<< orphan*/ ) ; 
 int uart_add_one_port (TYPE_1__*,TYPE_3__*) ; 
 int uart_register_driver (TYPE_1__*) ; 

__attribute__((used)) static int pl011_register_port(struct uart_amba_port *uap)
{
	int ret;

	/* Ensure interrupts from this UART are masked and cleared */
	pl011_write(0, uap, REG_IMSC);
	pl011_write(0xffff, uap, REG_ICR);

	if (!amba_reg.state) {
		ret = uart_register_driver(&amba_reg);
		if (ret < 0) {
			dev_err(uap->port.dev,
				"Failed to register AMBA-PL011 driver\n");
			return ret;
		}
	}

	ret = uart_add_one_port(&amba_reg, &uap->port);
	if (ret)
		pl011_unregister_port(uap);

	return ret;
}