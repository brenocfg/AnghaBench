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
typedef  int /*<<< orphan*/  u8 ;
struct uart_port {int dummy; } ;
struct TYPE_2__ {scalar_t__ membase; } ;
struct mps2_uart_port {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  readb (scalar_t__) ; 
 struct mps2_uart_port* to_mps2_port (struct uart_port*) ; 

__attribute__((used)) static u8 mps2_uart_read8(struct uart_port *port, unsigned int off)
{
	struct mps2_uart_port *mps_port = to_mps2_port(port);

	return readb(mps_port->port.membase + off);
}